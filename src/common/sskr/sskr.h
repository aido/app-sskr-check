//
//  sskr.h
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#ifndef SSKR_H
#define SSKR_H

#include <stdlib.h>
#include <stdint.h>

#include "sskr-constants.h"
#include "group.h"

int16_t sskr_count_shards(uint8_t group_threshold,
                          const sskr_group_descriptor_t *groups,
                          uint8_t groups_len);

/**
 * @brief Generate a set of shards that can be used to reconstruct a secret
 *        using the given group policy.
 *
 * @details This function splits a secret into multiple shards according to a defined group policy.
 *          To reconstruct the secret, a specific number of shards from different groups
 *          (`group_threshold`) must be combined.
 *
 * @param[in]  group_threshold      Minimum number of groups required for secret reconstruction.
 * @param[in]  groups               Pointer to an array of `sskr_group_descriptor_t` structures,
 *                                  defining the groups and their members.
 * @param[in]  groups_length        Number of groups in the `groups` array.
 * @param[in]  master_secret        Pointer to the secret to be split up (must be 16-32 bytes long
 *                                  and even).
 * @param[in]  master_secret_length Length of the `master_secret` array in bytes.
 * @param[out] shard_len            Pointer to a variable that will be filled with the length of
 *                                  each shard.
 * @param[out] output               Pointer to a buffer where the generated shards will be stored.
 * @param[in]  buffer_size          Maximum size of the `output` buffer in bytes.
 * @param[in]  random_generator     Pointer to a function that generates random data (same as in SSS
 *                                  functions).
 *
 * @return Number of shards generated on success, or a negative error code on failure.
 *         Specific error codes are implementation-specific, consult implementation details.
 */
int16_t sskr_generate_shards(uint8_t group_threshold,
                             const sskr_group_descriptor_t *groups,
                             uint8_t groups_length,
                             const uint8_t *master_secret,
                             uint16_t master_secret_length,
                             uint8_t *shard_len,
                             uint8_t *output,
                             uint16_t buffer_size,
                             unsigned char *(*random_generator)(uint8_t *, size_t));

/**
 * @brief Combines shards to reconstruct a secret.
 *
 * @details This function takes a collection of shards generated using `sskr_generate_shards`
 *          and reconstructs the original secret, assuming the provided shards meet
 *          the group threshold requirements. It employs Shamir's Secret Sharing (SSS)
 *          for secret reconstruction.
 *
 * @param[in]  input_shards  Pointer to an array of pointers to serialized shards.
 * @param[in]  shard_len     Length of each shard in bytes.
 * @param[in]  shards_count  Number of shards in the `input_shards` array.
 * @param[out] buffer        Pointer to a buffer where the reconstructed secret will be stored.
 * @param[in]  buffer_length Maximum size of the `buffer` in bytes.
 *
 * @return Length of the reconstructed secret on success, or a negative error code on failure.
 *         Specific error codes are implementation-specific, consult implementation details.
 */
int16_t sskr_combine_shards(const uint8_t **input_shards,
                            uint8_t shard_len,
                            uint8_t shards_count,
                            uint8_t *buffer,
                            uint16_t buffer_length);

#endif /* SSKR_H */
