//
//  sss.h
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#ifndef SSS_H
#define SSS_H

#include <stdint.h>
#include "sss-constants.h"

#define SSS_SECRET_INDEX 255
#define SSS_DIGEST_INDEX 254

/**
 * @brief Splits a secret into shares using Shamir's Secret Sharing (SSS) with SLIP-39 strategy.
 *
 * @details This function splits a secret into a specified number of shares (`share_count`)
 *          using SSS with a given threshold (`threshold`). To recover the secret, at least
 *          `threshold` shares must be combined. This implementation follows the strategy
 *          outlined in SLIP-39 for generating SSS shares.
 *
 * @param[in] threshold         Minimum number of shares required to recover the secret
 *                              (1 <= threshold <= share_count).
 * @param[in] share_count       Total number of shares to generate.
 * @param[in] secret            Pointer to the array containing the secret data.
 * @param[in] secret_length     Length of the `secret` array in bytes (must be between 16 and 32,
 *                              inclusive, and even).
 * @param[out] result           Pointer to a buffer where the generated shares will be stored.
 *                              The size of this buffer must be `share_count * secret_length` bytes.
 * @param[in] random_generator  A pointer to a function that generates random data. This function
 *                              must take two arguments: a pointer to a buffer and the size of the
 *                              buffer to fill with random bytes. The function should return 0 on
 *                              with random bytes. The function should return 0 on success or a
 *                              success or a negative value on failure.
 *
 * @return                      The number of shares created on success, or a negative value on
 *                              error:
 *                              - SSS_INVALID_ARGS: if threshold or share_count is invalid
 *                              - SSS_MEM_ALLOC_FAIL: if memory allocation fails
 *                              - SSS_RANDOM_FAILURE: if random data generation fails
 *                              - Other negative values may be returned by the `random_generator`
 *                                function.
 */
int16_t sss_split_secret(uint8_t threshold,
                         uint8_t share_count,
                         const uint8_t *secret,
                         uint8_t secret_length,
                         uint8_t *result,
                         unsigned char *(*random_generator)(uint8_t *, size_t));

/**
 * @brief Recovers a secret from Shamir's Secret Sharing (SSS) shares.
 *
 * @details This function recovers a secret from a set of SSS shares provided as `x` values
 *          and pointers to `y` value arrays (`shares`). To successfully recover the secret,
 *          at least `threshold` shares must be provided. This implementation follows the
 *          Lagrange polynomial interpolation method for SSS recovery.
 *
 * @param[in] threshold     Minimum number of shares required to recover the secret
 *                          (1 <= threshold <= share_count).
 * @param[in] x             Pointer to an array containing the x values (length: threshold).
 * @param[in] shares        Pointer to an array of length `threshold`, where each element is a
 *                          pointer to a y value array.
 * @param[in] share_length  Length of each y value array in bytes.
 * @param[out] secret       Pointer to a buffer where the recovered secret will be stored.
 *                          The size of this buffer must be at least `share_length` bytes.
 *
 * @return                  The number of bytes written to the `secret` array on success,
 *                          or a negative value on error:
 */
int16_t sss_recover_secret(uint8_t threshold,
                           const uint8_t *x,
                           const uint8_t **shares,
                           uint8_t share_length,
                           uint8_t *secret);

#endif /* SSS_H */
