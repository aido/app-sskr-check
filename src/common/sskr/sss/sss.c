//
//  sss.c
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include <string.h>
#include <cx.h>

#include "sss.h"
#include "interpolate.h"

/**
 * @brief Validates the parameters for Shamir's Secret Sharing (SSS) functions.
 *
 * @details This function checks if the provided threshold, share count, and
 *          secret length are within the acceptable ranges for SSS operations.
 *          It enforces constraints to ensure the integrity and security of the
 *          secret sharing process.
 *
 * @param[in] threshold     The minimum number of shares required to recover the secret.
 * @param[in] share_count   The total number of shares to be generated.
 * @param[in] secret_length The length of the secret in bytes.
 *
 * @return                  0 on success, or a negative error code on failure:
 *                          - SSS_ERROR_TOO_MANY_SHARES: if share_count exceeds SSS_MAX_SHARE_COUNT
 *                          - SSS_ERROR_INVALID_THRESHOLD: if threshold is invalid (< 1 or >
 *                            share_count)
 *                          - SSS_ERROR_SECRET_TOO_LONG: if secret_length exceeds
 *                            SSS_MAX_SECRET_SIZE
 *                          - SSS_ERROR_SECRET_TOO_SHORT: if secret_length is less than
 *                            SSS_MIN_SECRET_SIZE
 *                          - SSS_ERROR_SECRET_NOT_EVEN_LEN: if secret_length is not even
 */
static int16_t sss_validate_parameters(uint8_t threshold,
                                       uint8_t share_count,
                                       uint8_t secret_length) {
    if (share_count > SSS_MAX_SHARE_COUNT) {
        return SSS_ERROR_TOO_MANY_SHARES;
    } else if (threshold < 1 || threshold > share_count) {
        return SSS_ERROR_INVALID_THRESHOLD;
    } else if (secret_length > SSS_MAX_SECRET_SIZE) {
        return SSS_ERROR_SECRET_TOO_LONG;
    } else if (secret_length < SSS_MIN_SECRET_SIZE) {
        return SSS_ERROR_SECRET_TOO_SHORT;
    } else if (secret_length & 1) {
        return SSS_ERROR_SECRET_NOT_EVEN_LEN;
    }
    return 0;
}

/**
 * @brief Creates a digest used to help validate secret reconstruction (see SLIP-39 docs).
 *
 * @details This function takes random data, a shared secret, and calculates a 4-byte
 *          digest using HMAC. This digest can be used to verify the integrity of the
 *          reconstructed secret during Shamir's Secret Sharing (SSS) recovery process.
 *
 * @param[in]  random_data   Pointer to the array containing the random data.
 * @param[in]  rdlen         Length of the `random_data` array in bytes.
 * @param[in]  shared_secret Pointer to the array containing the shared secret.
 * @param[in]  sslen         Length of the `shared_secret` array in bytes.
 * @param[out] result        Pointer to a 4-byte array where the digest will be stored.
 *
 * @return                   Pointer to the `result` array containing the digest,
 *                           or `NULL` on failure.
 */
uint8_t *sss_create_digest(const uint8_t *random_data,
                           uint32_t rdlen,
                           const uint8_t *shared_secret,
                           uint32_t sslen,
                           uint8_t *result) {
    uint8_t buf[32];

    cx_hmac_sha256(random_data, rdlen, shared_secret, sslen, buf, sizeof(buf));

    for (uint8_t j = 0; j < 4; ++j) {
        result[j] = buf[j];
    }

    return result;
}

int16_t sss_split_secret(uint8_t threshold,
                         uint8_t share_count,
                         const uint8_t *secret,
                         uint8_t secret_length,
                         uint8_t *result,
                         unsigned char *(*random_generator)(uint8_t *, size_t)) {
    int16_t error = sss_validate_parameters(threshold, share_count, secret_length);
    if (error) {
        return error;
    }

    if (threshold == 1) {
        // just return share_count copies of the secret
        uint8_t *share = result;
        for (uint8_t i = 0; i < share_count; ++i, share += secret_length) {
            for (uint8_t j = 0; j < secret_length; ++j) {
                share[j] = secret[j];
            }
        }
        return share_count;
    } else {
        uint8_t digest[SSS_MAX_SECRET_SIZE];
        uint8_t x[SSS_MAX_SHARE_COUNT];
        const uint8_t *y[SSS_MAX_SHARE_COUNT];
        uint8_t n = 0;
        uint8_t *share = result;

        for (uint8_t i = 0; i < threshold - 2; ++i, share += secret_length) {
            random_generator(share, secret_length);
            x[n] = i;
            y[n] = share;
            n += 1;
        }

        // generate secret_length - 4 bytes worth of random data
        random_generator(digest + 4, secret_length - 4);
        // put 4 bytes of digest at the top of the digest array
        sss_create_digest(digest + 4, secret_length - 4, secret, secret_length, digest);
        x[n] = SSS_DIGEST_INDEX;
        y[n] = digest;
        n += 1;

        x[n] = SSS_SECRET_INDEX;
        y[n] = secret;
        n += 1;

        for (uint8_t i = threshold - 2; i < share_count; ++i, share += secret_length) {
            if (interpolate(n, x, secret_length, y, i, share) != CX_OK) {
                return SSS_ERROR_INTERPOLATION_FAILURE;
            }
        }

        memzero(digest, sizeof(digest));
        memzero(x, sizeof(x));
        memzero(y, sizeof(y));
    }
    return share_count;
}

int16_t sss_recover_secret(uint8_t threshold,
                           const uint8_t *x,
                           const uint8_t **shares,
                           uint8_t share_length,
                           uint8_t *secret) {
    int16_t error = sss_validate_parameters(threshold, threshold, share_length);
    if (error) {
        return error;
    }

    uint8_t digest[SSS_MAX_SECRET_SIZE];
    uint8_t verify[4];
    uint8_t valid = 1;

    if (threshold == 1) {
        for (uint8_t j = 0; j < share_length; ++j) {
            secret[j] = shares[0][j];
        }
        return share_length;
    }

    if (interpolate(threshold, x, share_length, shares, SSS_DIGEST_INDEX, digest) != CX_OK ||
        interpolate(threshold, x, share_length, shares, SSS_SECRET_INDEX, secret) != CX_OK) {
        memzero(secret, sizeof(digest));
        memzero(digest, sizeof(digest));
        memzero(verify, sizeof(verify));

        return SSS_ERROR_INTERPOLATION_FAILURE;
    }

    sss_create_digest(digest + 4, share_length - 4, secret, share_length, verify);

    for (uint8_t i = 0; i < 4; i++) {
        valid &= digest[i] == verify[i];
    }

    memzero(digest, sizeof(digest));
    memzero(verify, sizeof(verify));

    if (!valid) {
        return SSS_ERROR_CHECKSUM_FAILURE;
    }

    return share_length;
}
