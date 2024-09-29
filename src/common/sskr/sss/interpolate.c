//
//  interpolate.c
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "os.h"
#include "ox_bn.h"
#include "cx_errors.h"

#include "interpolate.h"

// The irreducible polynomial N(x) = x^8 + x^4 + x^3 + x + 1
#define SSS_POLYNOMIAL \
    { 0x01, 0x1B }

// 2nd Montgomery constant: R2 = x^(2*t*8) mod N(x)
// t = 1 since the number of bytes of R is 1.
#define MONTGOMERY_CONSTANT_R2 \
    { 0x02 }

// Minimal required bytes for BN storing a GF(256) value
#define GF2_8_MPI_BYTES 16

#if defined(TARGET_NANOS) && !defined API_LEVEL
/**
 * @brief Performs a multiplication over GF(2^n).
 *
 * @details *bn_r* must be distinct from *bn_a* and *bn_b*.
 *
 * @param[out] bn_r BN index for the result.
 *
 * @param[in]  bn_a BN index of the first operand.
 *
 * @param[in]  bn_b BN index of the second operand.
 *
 * @param[in]  bn_n BN index of the modulus.
 *                  The modulus must be an irreducible polynomial over GF(2)
 *                  of degree n.
 *
 * @param[in]  bn_h BN index of the second montgomery constant.
 *
 * @return          Error code:
 *                  - CX_OK on success
 *                  - CX_NOT_LOCKED
 *                  - CX_INVALID_PARAMETER
 *                  - CX_MEMORY_FULL
 */
cx_err_t cx_bn_gf2_n_mul(cx_bn_t bn_r,
                         const cx_bn_t bn_a,
                         const cx_bn_t bn_b,
                         const cx_bn_t bn_n,
                         const cx_bn_t bn_h __attribute__((unused))) {
    cx_err_t error = CX_OK;
    uint32_t degree, nbits_a, nbits_b;

    // Ensure bn_r is distinct from bn_a and bn_b
    if (bn_r == bn_a || bn_r == bn_b) {
        error = CX_INVALID_PARAMETER;
        goto end;
    }

    // Calculate the degree of the modulus polynomial
    CX_CHECK(cx_bn_cnt_bits(bn_n, &degree));
    degree--;

    CX_CHECK(cx_bn_cnt_bits(bn_a, &nbits_a));
    CX_CHECK(cx_bn_cnt_bits(bn_b, &nbits_b));

    // Ensure both operands are in field
    if (degree < 1 || nbits_a > degree || nbits_b > degree) {
        error = CX_INVALID_PARAMETER;
        goto end;
    }

    // Preliminaries
    cx_bn_t bn_tempa, bn_copy;
    uint32_t bit_indexb = 0;
    size_t nbytes;
    bool bit_set = 0;

    CX_CHECK(cx_bn_nbytes(bn_n, &nbytes));
    CX_CHECK(cx_bn_alloc(&bn_tempa, nbytes));
    CX_CHECK(cx_bn_alloc(&bn_copy, nbytes));

    CX_CHECK(cx_bn_copy(bn_tempa, bn_a));
    CX_CHECK(cx_bn_set_u32(bn_r, (uint32_t) 0));

    // Main loop for multiplication
    if (nbits_a) {
        while (nbits_b > bit_indexb) {
            CX_CHECK(cx_bn_tst_bit(bn_b, bit_indexb, &bit_set));
            if (bit_set) {
                CX_CHECK(cx_bn_copy(bn_copy, bn_r));
                CX_CHECK(cx_bn_xor(bn_r, bn_tempa, bn_copy));
            }

            CX_CHECK(cx_bn_shl(bn_tempa, 1));
            CX_CHECK(cx_bn_tst_bit(bn_tempa, degree, &bit_set));

            if (bit_set) {
                CX_CHECK(cx_bn_copy(bn_copy, bn_tempa));
                CX_CHECK(cx_bn_xor(bn_tempa, bn_n, bn_copy));
            }

            bit_indexb++;
        }
    }

    // Clean up
    CX_CHECK(cx_bn_destroy(&bn_tempa));
    CX_CHECK(cx_bn_destroy(&bn_copy));

end:
    return error;
}
#endif

cx_err_t interpolate(uint8_t n,
                     const uint8_t* xi,
                     uint8_t yl,
                     const uint8_t** yij,
                     uint8_t x,
                     uint8_t* result) {
    const uint8_t N[2] = SSS_POLYNOMIAL;
    const uint8_t R2[1] = MONTGOMERY_CONSTANT_R2;

    cx_err_t error = CX_OK;  // By default, until some error occurs
    cx_bn_t bn_x, bn_xc_i;
    cx_bn_t bn_numerator, bn_lagrange;
    cx_bn_t bn_result, bn_tempa, bn_tempb, bn_tempc, bn_n, bn_r2;
    uint32_t result_u32;

    CX_CHECK(cx_bn_lock(GF2_8_MPI_BYTES, 0));
    CX_CHECK(cx_bn_alloc(&bn_x, GF2_8_MPI_BYTES));
    CX_CHECK(cx_bn_alloc(&bn_xc_i, GF2_8_MPI_BYTES));
    CX_CHECK(cx_bn_alloc(&bn_numerator, GF2_8_MPI_BYTES));
    CX_CHECK(cx_bn_alloc(&bn_lagrange, GF2_8_MPI_BYTES));
    CX_CHECK(cx_bn_alloc(&bn_result, GF2_8_MPI_BYTES));
    CX_CHECK(cx_bn_alloc(&bn_tempa, GF2_8_MPI_BYTES));
    CX_CHECK(cx_bn_alloc(&bn_tempb, GF2_8_MPI_BYTES));
    CX_CHECK(cx_bn_alloc(&bn_tempc, GF2_8_MPI_BYTES));
    CX_CHECK(cx_bn_alloc_init(&bn_n, GF2_8_MPI_BYTES, N, sizeof(N)));
    CX_CHECK(cx_bn_alloc_init(&bn_r2, GF2_8_MPI_BYTES, R2, sizeof(R2)));

    CX_CHECK(cx_bn_set_u32(bn_x, (uint32_t) x));
    memzero(result, yl);

    for (uint8_t i = 0; i < n; i++) {
        CX_CHECK(cx_bn_set_u32(bn_xc_i, (uint32_t) xi[i]));
        CX_CHECK(cx_bn_set_u32(bn_lagrange, (uint32_t) 1));

        // calculate the lagrange basis coefficient for the lagrange polynomial
        // defined by the x coordinates xi at the value x.
        //
        // After loop runs, bn_lagrange should hold data satisfying
        // the following:
        //                ---     (x-xi[j])
        // bn_lagrange =  | |   -------------
        //              j != i  (xi[i]-xi[j])
        for (uint8_t j = 0; j < n; j++) {
            if (j != i) {
                CX_CHECK(cx_bn_set_u32(bn_tempa, (uint32_t) xi[j]));

                // Calculate the numerator (x - xc[j])
                CX_CHECK(cx_bn_xor(bn_numerator, bn_x, bn_tempa));

                // Calculate the denominator (xc[i] - xc[j])
                CX_CHECK(cx_bn_xor(bn_tempb, bn_xc_i, bn_tempa));

                // Calculate the inverse of the denominator
                // In GF(2^8) the inverse of x = x^254
                // bn_tempa = denominator^2
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempa, bn_tempb, bn_tempb, bn_n, bn_r2));
                // bn_result = denominator^4
                CX_CHECK(cx_bn_gf2_n_mul(bn_result, bn_tempa, bn_tempa, bn_n, bn_r2));
                // bn_tempa = denominator^8
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempa, bn_result, bn_result, bn_n, bn_r2));
                // bn_tempc = denominator^9
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempc, bn_tempa, bn_tempb, bn_n, bn_r2));
                // bn_tempb = denominator^16
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempb, bn_tempa, bn_tempa, bn_n, bn_r2));
                // bn_tempa = denominator^25
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempa, bn_tempb, bn_tempc, bn_n, bn_r2));
                // bn_tempb = denominator^50
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempb, bn_tempa, bn_tempa, bn_n, bn_r2));
                // bn_tempc = denominator^100
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempc, bn_tempb, bn_tempb, bn_n, bn_r2));
                // bn_tempa = denominator^200
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempa, bn_tempc, bn_tempc, bn_n, bn_r2));
                // bn_tempc = denominator^250
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempc, bn_tempa, bn_tempb, bn_n, bn_r2));
                // bn_tempb = denominator^254
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempb, bn_result, bn_tempc, bn_n, bn_r2));

                // Calculate the lagrange basis coefficient
                CX_CHECK(cx_bn_gf2_n_mul(bn_tempa, bn_numerator, bn_lagrange, bn_n, bn_r2));
                CX_CHECK(cx_bn_gf2_n_mul(bn_lagrange, bn_tempa, bn_tempb, bn_n, bn_r2));
            }
        }

        for (uint8_t j = 0; j < yl; j++) {
            CX_CHECK(cx_bn_set_u32(bn_tempa, (uint32_t) yij[i][j]));
            CX_CHECK(cx_bn_set_u32(bn_tempb, (uint32_t) result[j]));

            CX_CHECK(cx_bn_gf2_n_mul(bn_tempc, bn_lagrange, bn_tempa, bn_n, bn_r2));
            CX_CHECK(cx_bn_xor(bn_result, bn_tempb, bn_tempc));
            CX_CHECK(cx_bn_get_u32(bn_result, &result_u32));
            result[j] = (uint8_t) result_u32;
            result_u32 = 0;
        }
    }

    // clean up stack
    CX_CHECK(cx_bn_destroy(&bn_x));
    CX_CHECK(cx_bn_destroy(&bn_xc_i));
    CX_CHECK(cx_bn_destroy(&bn_numerator));
    CX_CHECK(cx_bn_destroy(&bn_lagrange));
    CX_CHECK(cx_bn_destroy(&bn_result));
    CX_CHECK(cx_bn_destroy(&bn_tempa));
    CX_CHECK(cx_bn_destroy(&bn_tempb));
    CX_CHECK(cx_bn_destroy(&bn_tempc));
    CX_CHECK(cx_bn_destroy(&bn_n));
    CX_CHECK(cx_bn_destroy(&bn_r2));

end:
    if (cx_bn_is_locked()) {
        cx_bn_unlock();
    }

    return error;
}
