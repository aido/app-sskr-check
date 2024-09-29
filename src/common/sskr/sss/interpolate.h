//
//  interpolate.h
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#define memzero(...) explicit_bzero(__VA_ARGS__)

/**
 * @brief Performs polynomial interpolation on SSS shares.
 *
 * @details This function interpolates a polynomial that passes through the provided points
 *          represented by `xi` (x-coordinates) and `yij` (y-coordinate arrays) i.e.
 *          where:
 *                 xi points to [x0 x1 ... xn-1 ]
 *                 y contains an array of pointers to 32-bit arrays of y values
 *                 y contains [y0 y1 y2 ... yn-1]
 *                 and each of the yi arrays contain [yi_0 yi_i ... yi_31].
 *
 *          This interpolation is used in Shamir's Secret Sharing (SSS) to recover
 *          the secret from a set of shares.
 *
 * @param[in]  n      Number of points to interpolate (length of `xi` and `yij`).
 * @param[in]  xi     Pointer to an array containing the x-coordinates of the points (length `n`).
 * @param[in]  yl     Length of each y-coordinate array in bytes.
 * @param[in]  yij    Pointer to an array of `n` pointers, each pointing to a y-coordinate array of
 *                    length `yl`.
 * @param[in]  x      X-coordinate at which to perform the interpolation.
 * @param[out] result Pointer to a buffer where the interpolated value will be stored (must be `yl
 *                    bytes long).
 *
 * @return            - CX_OK on success
 *                    - A negative error code on failure (specific error codes not defined here,
 *                      consult implementation details for specific error handling)
 */
cx_err_t interpolate(uint8_t n,
                     const uint8_t* xi,
                     uint8_t yl,
                     const uint8_t** yij,
                     uint8_t x,
                     uint8_t* result);

#endif /* INTERPOLATE_H */
