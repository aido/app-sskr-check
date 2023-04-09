/*
 * Implementation of the hazardous parts of the SSS library
 *
 * Author: Daan Sprenkels <hello@dsprenkels.com>
 * Copyright (c) 2017 Daan Sprenkels <hello@dsprenkels.com>
 *
 * Licensed under the "MIT License"
 *
 * This code contains the actual Shamir secret sharing functionality. The
 * implementation of this code is based on the idea that the user likes to
 * generate/combine 32 shares (in GF(2^8) at the same time, because a 256 bit
 * key will be exactly 32 bytes. Therefore we bitslice all the input and
 * unbitslice the output right before returning.
 *
 * This bitslice approach optimizes natively on all architectures that are 32
 * bit or more. Care is taken to use not too many registers, to ensure that no
 * values have to be leaked to the stack.
 *
 * All functions in this module are implemented constant time and constant
 * lookup operations, as all proper crypto code must be.
 */

#include <string.h>
#include "hazmat.h"
#include "memzero.h"

/**
 * bitslice - Transpose bits of 32 bytes to form 8 32-bit words.
 *
 * This function transposes the bits of an input 32-byte array x into
 * 8 32-bit words, stored in the output array r.
 *
 * @param r [out] 8-element array of 32-bit words, where the transposed bits will be stored.
 * @param x [in] 32-element byte array to be transposed.
 */
void bitslice(uint32_t r[8], const uint8_t x[32]) {
    // Securely wipe the memory of the output array
    memzero(r, sizeof(uint32_t[8]));

    // Iterate over each byte in the input array
    for (size_t arr_idx = 0; arr_idx < 32; arr_idx++) {
        uint32_t cur = (uint32_t) x[arr_idx];

        // Iterate over each bit in the current byte
        for (size_t bit_idx = 0; bit_idx < 8; bit_idx++) {
            // Transpose the current bit into the appropriate position in the output array
            r[bit_idx] |= ((cur & (1 << bit_idx)) >> bit_idx) << arr_idx;
        }
    }
}

/**
 * unbitslice - Reverse the bitslicing operation performed by bitslice().
 *
 * This function reverses the bitslicing operation, converting 8 32-bit words
 * back into a 32-byte array. It is essentially the inverse operation of the bitslice() function.
 *
 * @param r [out] 32-element byte array, where the unbitsliced data will be stored.
 * @param x [in] 8-element array of 32-bit words to be unbitsliced.
 */
void unbitslice(uint8_t r[32], const uint32_t x[8]) {
    // Securely wipe the memory of the output array
    memzero(r, sizeof(uint8_t[32]));

    // Iterate over each 32-bit word in the input array
    for (size_t bit_idx = 0; bit_idx < 8; bit_idx++) {
        uint32_t cur = (uint32_t) x[bit_idx];

        // Iterate over each bit in the current 32-bit word
        for (size_t arr_idx = 0; arr_idx < 32; arr_idx++) {
            // Transpose the current bit into the appropriate position in the output array
            r[arr_idx] |= ((cur & (((uint32_t) 1) << arr_idx)) >> arr_idx) << bit_idx;
        }
    }
}

/**
 * bitslice_setall - Set all bits in an 8-element 32-bit words array based on the input byte.
 *
 * This function sets the bits in the output array 'r' based on the input byte 'x'.
 * For each bit 'i' in 'x', if it is set, the corresponding 32-bit word in 'r' will have all bits
 * set; otherwise, the corresponding word will have all bits unset.
 *
 * @param r [out] 8-element array of 32-bit words, where the resulting data will be stored.
 * @param x [in] Input byte to determine the bit values in the output array.
 */
void bitslice_setall(uint32_t r[8], const uint8_t x) {
    // Iterate over each bit in the input byte
    for (size_t idx = 0; idx < 8; idx++) {
        // Set all bits in r[idx] based on the corresponding bit in x
        // cppcheck-suppress shiftTooManyBitsSigned
        r[idx] = ((int32_t) ((x & (((uint32_t) 1) << idx)) << (31 - idx))) >> 31;
    }
}

/**
 * gf256_add - Add (XOR) two 8-element arrays of 32-bit words element-wise.
 *
 * This function performs an element-wise addition (XOR) of the input arrays 'r' and 'x'
 * and stores the result back in the 'r' array. The operation is performed in GF(2^8).
 *
 * @param r [in, out] 8-element array of 32-bit words, where one of the input arrays and the result
 * will be stored.
 * @param x [in] 8-element array of 32-bit words, the other input array.
 */
void gf256_add(uint32_t r[8], const uint32_t x[8]) {
    // Iterate over each element in the input arrays
    for (size_t idx = 0; idx < 8; idx++) {
        // Perform element-wise XOR (addition in GF(2^8)) and store the result in r
        r[idx] ^= x[idx];
    }
}

/**
 * gf256_mul - Multiply two bitsliced polynomials in GF(2^8) reduced by x^8 + x^4 + x^3 + x + 1.
 *
 * This function multiplies two bitsliced polynomials 'a' and 'b' in GF(2^8) and stores the result
 * in the output array 'r'. The multiplication is performed using Russian Peasant multiplication
 * and the polynomials are reduced by x^8 + x^4 + x^3 + x + 1.
 *
 * Note: 'r' and 'a' may overlap, but overlapping of 'r' and 'b' will produce an incorrect result!
 * If you need to square a polynomial, use `gf256_square` instead.
 *
 * @param r [out] 8-element array of 32-bit words, where the resulting data will be stored.
 * @param a [in] 8-element array of 32-bit words, one of the input polynomials.
 * @param b [in] 8-element array of 32-bit words, the other input polynomial.
 */
void gf256_mul(uint32_t r[8], const uint32_t a[8], const uint32_t b[8]) {
    /* This function implements Russian Peasant multiplication on two
     * bitsliced polynomials.
     *
     * I personally think that these kinds of long lists of operations
     * are often a bit ugly. A double for loop would be nicer and would
     * take up a lot less lines of code.
     * However, some compilers seem to fail in optimizing these kinds of
     * loops. So we will just have to do this by hand.
     */
    uint32_t a2[8];
    memcpy(a2, a, sizeof(uint32_t[8]));

    r[0] = a2[0] & b[0]; /* add (assignment, because r is 0) */
    r[1] = a2[1] & b[0];
    r[2] = a2[2] & b[0];
    r[3] = a2[3] & b[0];
    r[4] = a2[4] & b[0];
    r[5] = a2[5] & b[0];
    r[6] = a2[6] & b[0];
    r[7] = a2[7] & b[0];
    a2[0] ^= a2[7]; /* reduce */
    a2[2] ^= a2[7];
    a2[3] ^= a2[7];

    r[0] ^= a2[7] & b[1]; /* add */
    r[1] ^= a2[0] & b[1];
    r[2] ^= a2[1] & b[1];
    r[3] ^= a2[2] & b[1];
    r[4] ^= a2[3] & b[1];
    r[5] ^= a2[4] & b[1];
    r[6] ^= a2[5] & b[1];
    r[7] ^= a2[6] & b[1];
    a2[7] ^= a2[6]; /* reduce */
    a2[1] ^= a2[6];
    a2[2] ^= a2[6];

    r[0] ^= a2[6] & b[2]; /* add */
    r[1] ^= a2[7] & b[2];
    r[2] ^= a2[0] & b[2];
    r[3] ^= a2[1] & b[2];
    r[4] ^= a2[2] & b[2];
    r[5] ^= a2[3] & b[2];
    r[6] ^= a2[4] & b[2];
    r[7] ^= a2[5] & b[2];
    a2[6] ^= a2[5]; /* reduce */
    a2[0] ^= a2[5];
    a2[1] ^= a2[5];

    r[0] ^= a2[5] & b[3]; /* add */
    r[1] ^= a2[6] & b[3];
    r[2] ^= a2[7] & b[3];
    r[3] ^= a2[0] & b[3];
    r[4] ^= a2[1] & b[3];
    r[5] ^= a2[2] & b[3];
    r[6] ^= a2[3] & b[3];
    r[7] ^= a2[4] & b[3];
    a2[5] ^= a2[4]; /* reduce */
    a2[7] ^= a2[4];
    a2[0] ^= a2[4];

    r[0] ^= a2[4] & b[4]; /* add */
    r[1] ^= a2[5] & b[4];
    r[2] ^= a2[6] & b[4];
    r[3] ^= a2[7] & b[4];
    r[4] ^= a2[0] & b[4];
    r[5] ^= a2[1] & b[4];
    r[6] ^= a2[2] & b[4];
    r[7] ^= a2[3] & b[4];
    a2[4] ^= a2[3]; /* reduce */
    a2[6] ^= a2[3];
    a2[7] ^= a2[3];

    r[0] ^= a2[3] & b[5]; /* add */
    r[1] ^= a2[4] & b[5];
    r[2] ^= a2[5] & b[5];
    r[3] ^= a2[6] & b[5];
    r[4] ^= a2[7] & b[5];
    r[5] ^= a2[0] & b[5];
    r[6] ^= a2[1] & b[5];
    r[7] ^= a2[2] & b[5];
    a2[3] ^= a2[2]; /* reduce */
    a2[5] ^= a2[2];
    a2[6] ^= a2[2];

    r[0] ^= a2[2] & b[6]; /* add */
    r[1] ^= a2[3] & b[6];
    r[2] ^= a2[4] & b[6];
    r[3] ^= a2[5] & b[6];
    r[4] ^= a2[6] & b[6];
    r[5] ^= a2[7] & b[6];
    r[6] ^= a2[0] & b[6];
    r[7] ^= a2[1] & b[6];
    a2[2] ^= a2[1]; /* reduce */
    a2[4] ^= a2[1];
    a2[5] ^= a2[1];

    r[0] ^= a2[1] & b[7]; /* add */
    r[1] ^= a2[2] & b[7];
    r[2] ^= a2[3] & b[7];
    r[3] ^= a2[4] & b[7];
    r[4] ^= a2[5] & b[7];
    r[5] ^= a2[6] & b[7];
    r[6] ^= a2[7] & b[7];
    r[7] ^= a2[0] & b[7];
}

/*
 * Square `x` in GF(2^8) and write the result to `r`. `r` and `x` may overlap.
 */
void gf256_square(uint32_t r[8], const uint32_t x[8]) {
    uint32_t r8, r10, r12, r14;
    /* Use the Freshman's Dream rule to square the polynomial
     * Assignments are done from 7 downto 0, because this allows the user
     * to execute this function in-place (e.g. `gf256_square(r, r);`).
     */
    r14 = x[7];
    r12 = x[6];
    r10 = x[5];
    r8 = x[4];
    r[6] = x[3];
    r[4] = x[2];
    r[2] = x[1];
    r[0] = x[0];

    /* Reduce with  x^8 + x^4 + x^3 + x + 1 until order is less than 8 */
    r[7] = r14; /* r[7] was 0 */
    r[6] ^= r14;
    r10 ^= r14;
    /* Skip, because r13 is always 0 */
    r[4] ^= r12;
    r[5] = r12; /* r[5] was 0 */
    r[7] ^= r12;
    r8 ^= r12;
    /* Skip, because r11 is always 0 */
    r[2] ^= r10;
    r[3] = r10; /* r[3] was 0 */
    r[5] ^= r10;
    r[6] ^= r10;
    r[1] = r14;  /* r[1] was 0 */
    r[2] ^= r14; /* Substitute r9 by r14 because they will always be equal*/
    r[4] ^= r14;
    r[5] ^= r14;
    r[0] ^= r8;
    r[1] ^= r8;
    r[3] ^= r8;
    r[4] ^= r8;
}

/*
 * Invert `x` in GF(2^8) and write the result to `r`
 */
void gf256_inv(uint32_t r[8], uint32_t x[8]) {
    uint32_t y[8], z[8];

    gf256_square(y, x);  // y = x^2
    gf256_square(y, y);  // y = x^4
    gf256_square(r, y);  // r = x^8
    gf256_mul(z, r, x);  // z = x^9
    gf256_square(r, r);  // r = x^16
    gf256_mul(r, r, z);  // r = x^25
    gf256_square(r, r);  // r = x^50
    gf256_square(z, r);  // z = x^100
    gf256_square(z, z);  // z = x^200
    gf256_mul(r, r, z);  // r = x^250
    gf256_mul(r, r, y);  // r = x^254
}

#if 0

/*
 * Create `k` key shares of the key given in `key`. The caller has to ensure
 * that the array `out` has enough space to hold at least `n` sss_Keyshare
 * structs.
 */
 void
 sss_create_keyshares(sss_Keyshare *out,
                      const uint8_t key[32],
                      uint8_t n,
                      uint8_t k)
{
	/* Check if the parameters are valid */
	assert(n != 0);
	assert(k != 0);
	assert(k <= n);

	uint8_t share_idx, coeff_idx, unbitsliced_x;
	uint32_t poly0[8], poly[k-1][8], x[8], y[8], xpow[8], tmp[8];

	/* Put the secret in the bottom part of the polynomial */
	bitslice(poly0, key);

	/* Generate the other terms of the polynomial */
	randombytes((void*) poly, sizeof(poly));

	for (share_idx = 0; share_idx < n; share_idx++) {
		/* x value is in 1..n */
		unbitsliced_x = share_idx + 1;
		out[share_idx][0] = unbitsliced_x;
		bitslice_setall(x, unbitsliced_x);

		/* Calculate y */
		memzero(y, sizeof(y));
		memzero(xpow, sizeof(xpow));
		xpow[0] = ~0;
		gf256_add(y, poly0);
		for (coeff_idx = 0; coeff_idx < (k-1); coeff_idx++) {
			gf256_mul(xpow, xpow, x);
			gf256_mul(tmp, xpow, poly[coeff_idx]);
			gf256_add(y, tmp);
		}
		unbitslice(&out[share_idx][1], y);
	}
}


/*
 * Restore the `k` sss_Keyshare structs given in `shares` and write the result
 * to `key`.
 */
 void sss_combine_keyshares(uint8_t key[32],
                            const sss_Keyshare *key_shares,
                            uint8_t k)
{
	size_t share_idx, idx1, idx2;
	uint32_t xs[k][8], ys[k][8];
	uint32_t num[8], denom[8], tmp[8];
	uint32_t secret[8] = {0};

	/* Collect the x and y values */
	for (share_idx = 0; share_idx < k; share_idx++) {
		bitslice_setall(xs[share_idx], key_shares[share_idx][0]);
		bitslice(ys[share_idx], &key_shares[share_idx][1]);
	}

	/* Use Lagrange basis polynomials to calculate the secret coefficient */
	for (idx1 = 0; idx1 < k; idx1++) {
		memzero(num, sizeof(num));
		memzero(denom, sizeof(denom));
		num[0] = ~0; /* num is the numerator (=1) */
		denom[0] = ~0; /* denom is the numerator (=1) */
		for (idx2 = 0; idx2 < k; idx2++) {
			if (idx1 == idx2) continue;
			gf256_mul(num, num, xs[idx2]);
			memcpy(tmp, xs[idx1], sizeof(uint32_t[8]));
			gf256_add(tmp, xs[idx2]);
			gf256_mul(denom, denom, tmp);
		}
		gf256_inv(tmp, denom); /* inverted denominator */
		gf256_mul(num, num, tmp); /* basis polynomial */
		gf256_mul(num, num, ys[idx1]); /* scaled coefficient */
		gf256_add(secret, num);
	}
	unbitslice(key, secret);
}

#endif
