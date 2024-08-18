/* @BANNER@ */

#include <string.h>
#include <os.h>
#include <cx.h>

#include "onboarding_seed_rom_variables.h"
#include "common_bip39.h"
#include "sskr.h"

// Return the CRC-32 checksum of the input buffer in network byte order (big endian).
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define crc32_nbo(...) cx_crc32(__VA_ARGS__)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define crc32_nbo(...) os_swap_u32(cx_crc32(__VA_ARGS__))
#else
#error "What kind of system is this?"
#endif

int16_t bolos_ux_sskr_size_get(uint8_t bip39_onboarding_kind,
                               uint8_t groups_threshold,
                               unsigned int *group_descriptor,
                               uint8_t groups_len,
                               uint8_t *share_len) {
    sskr_group_descriptor_t groups[SSKR_MAX_GROUP_COUNT];
    for (uint8_t i = 0; i < groups_len; i++) {
        groups[i].threshold = *(group_descriptor + i * sizeof(*(group_descriptor)) / groups_len);
        groups[i].count = *(group_descriptor + 1 + i * sizeof(*(group_descriptor)) / groups_len);
    }

    int16_t share_count_expected = sskr_count_shards(groups_threshold, groups, groups_len);
    *share_len = bip39_onboarding_kind * 4 / 3 + SSKR_METADATA_LENGTH_BYTES;

    return share_count_expected;
}

unsigned int bolos_ux_sskr_combine(unsigned char *sskr_shares_hex,
                                   unsigned int sskr_shares_hex_length,
                                   unsigned int sskr_shares_count,
                                   unsigned char *output) {
    const uint8_t *ptr_sskr_shares[SSKR_MAX_GROUP_COUNT * SSS_MAX_SHARE_COUNT];
    uint8_t sskr_share_len = sskr_shares_hex[3] & 0x1F;
    if (sskr_share_len > 23) {
        sskr_share_len = sskr_shares_hex[4];
    }

    for (uint8_t i = 0; i < (uint8_t) sskr_shares_count; i++) {
        ptr_sskr_shares[i] = sskr_shares_hex + (i * sskr_shares_hex_length / sskr_shares_count) +
                             4 + (sskr_share_len > 23);
    }

    uint16_t output_len = sskr_combine_shards(ptr_sskr_shares,
                                              sskr_share_len,
                                              (uint8_t) sskr_shares_count,
                                              output,
                                              SSKR_MAX_STRENGTH_BYTES);

    if (output_len < 1) {
        memzero(sskr_shares_hex, sizeof(sskr_shares_hex));
        return 0;
    }

    PRINTF("SSKR decoded shares:\n %.*H\n", output_len, output);
    return (unsigned int) output_len;
}

void bolos_ux_sskr_to_seed_convert(unsigned char *sskr_shares_hex,
                                   unsigned int sskr_shares_hex_length,
                                   unsigned int sskr_shares_count,
                                   unsigned char *words_buffer,
                                   unsigned int *words_buffer_length,
                                   unsigned char *seed) {
    PRINTF("SSKR share in hex:\n %.*H\n", sskr_shares_hex_length, sskr_shares_hex);

    uint8_t seed_buffer[SSKR_MAX_STRENGTH_BYTES] = {0};
    uint8_t seed_buffer_len = bolos_ux_sskr_combine(sskr_shares_hex,
                                                    sskr_shares_hex_length,
                                                    sskr_shares_count,
                                                    seed_buffer);

    *words_buffer_length = bolos_ux_bip39_mnemonic_encode(seed_buffer,
                                                          (uint8_t) seed_buffer_len,
                                                          words_buffer,
                                                          *words_buffer_length);
    memzero(seed_buffer, sizeof(seed_buffer));
    bolos_ux_bip39_mnemonic_to_seed(words_buffer, *words_buffer_length, seed);
}

unsigned int bolos_ux_sskr_generate(uint8_t groups_threshold,
                                    unsigned int *group_descriptor,
                                    uint8_t groups_len,
                                    unsigned char *seed,
                                    unsigned int seed_len,
                                    uint8_t *share_len,
                                    unsigned char *share_buffer,
                                    unsigned int share_buffer_len,
                                    uint8_t share_len_expected,
                                    int16_t share_count_expected) {
    sskr_group_descriptor_t groups[SSKR_MAX_GROUP_COUNT];

    for (uint8_t i = 0; i < (uint8_t) groups_len; i++) {
        groups[i].threshold = *(group_descriptor + i * 2);
        groups[i].count = *(group_descriptor + 1 + i * 2);
    }

    if (!(SSKR_MIN_STRENGTH_BYTES <= seed_len && seed_len <= SSKR_MAX_STRENGTH_BYTES) ||
        (seed_len % 2 != 0)) {
        return 0;
    }

    PRINTF("SSKR generate input:\n %.*H\n", seed_len, seed);
    // convert seed to SSKR shares
    int16_t share_count = sskr_generate_shards(groups_threshold,
                                               groups,
                                               groups_len,
                                               seed,
                                               seed_len,
                                               share_len,
                                               share_buffer,
                                               share_buffer_len,
                                               cx_rng);

    PRINTF("SSKR share count expected: %d\n", share_count_expected);
    PRINTF("SSKR share count returned: %d\n", share_count);
    PRINTF("SSKR share length expected: %d\n", share_len_expected);
    PRINTF("SSKR share length returned: %d\n", *share_len);

    if ((share_count < 0) || (share_count != share_count_expected) ||
        (*share_len != share_len_expected)) {
        memzero(&share_buffer, sizeof(share_buffer));
        return 0;
    }

    PRINTF("SSKR generate output:\n %.*H\n", share_buffer_len, share_buffer);

    return share_count;
}

unsigned int bolos_ux_sskr_share_hex_decode(unsigned char *input,
                                            unsigned int input_len,
                                            unsigned char *output,
                                            unsigned int output_len) {
    unsigned int position = 0;
    unsigned int offset = 0;

    for (uint8_t i = 0; i < (uint8_t) input_len; i++) {
        offset = SSKR_BYTEWORD_LENGTH * input[i];
        if (position + SSKR_BYTEWORD_LENGTH <= output_len) {
            memcpy(output + position, SSKR_WORDLIST + offset, SSKR_BYTEWORD_LENGTH);
        } else {
            memzero(output, sizeof(output));
            return 0;
        }
        position += SSKR_BYTEWORD_LENGTH;
        if (position < output_len) {
            output[position++] = ' ';
        }
    }
    PRINTF("SSKR share:\n %.*s\n", output_len, output);
    return position;
}

unsigned int bolos_ux_sskr_byteword_to_hex(unsigned char *byteword) {
    for (unsigned int i = 0; i < SSKR_WORDLIST_LENGTH; i += SSKR_BYTEWORD_LENGTH) {
        if (os_secure_memcmp((void *) (SSKR_WORDLIST + i), byteword, SSKR_BYTEWORD_LENGTH) == 0) {
            return i / SSKR_BYTEWORD_LENGTH;
        }
    }
    // no match, sry
    return SSKR_WORDLIST_LENGTH / SSKR_BYTEWORD_LENGTH;
}

unsigned int bolos_ux_bip39_to_sskr_convert(unsigned char *bip39_words_buffer,
                                            unsigned int bip39_words_buffer_length,
                                            unsigned int bip39_onboarding_kind,
                                            unsigned int *group_descriptor,
                                            uint8_t *share_count,
                                            unsigned char *share_words_buffer,
                                            unsigned int *share_words_buffer_length) {
    // get seed from bip39 mnemonic
    uint8_t seed_len = bip39_onboarding_kind * 4 / 3;
    uint8_t seed_buffer[SSKR_MAX_STRENGTH_BYTES + 1];

    if (bolos_ux_bip39_mnemonic_decode(bip39_words_buffer,
                                       bip39_words_buffer_length,
                                       seed_buffer,
                                       seed_len + 1) == 1) {
        memzero(bip39_words_buffer, sizeof(bip39_words_buffer));
        uint8_t groups_len = 1;
        uint8_t groups_threshold = 1;
        uint8_t share_len_expected = 0;
        int16_t share_count_expected = bolos_ux_sskr_size_get(bip39_onboarding_kind,
                                                              groups_threshold,
                                                              group_descriptor,
                                                              groups_len,
                                                              &share_len_expected);

        uint16_t share_hex_buffer_len = share_count_expected * share_len_expected;
        uint8_t share_hex_buffer[SSKR_MAX_GROUP_COUNT * SSS_MAX_SHARE_COUNT *
                                 (SSKR_MAX_STRENGTH_BYTES + SSKR_METADATA_LENGTH_BYTES)];
        uint8_t share_len = 0;
        *share_count = bolos_ux_sskr_generate(groups_threshold,
                                              group_descriptor,
                                              groups_len,
                                              seed_buffer,
                                              seed_len,
                                              &share_len,
                                              share_hex_buffer,
                                              share_hex_buffer_len,
                                              share_len_expected,
                                              share_count_expected);
        memzero(seed_buffer, sizeof(seed_buffer));
        if (*share_count > 0) {
            // CBOR Tag #6.40309 is D9 9D75
            // CBOR Major type 2 is 0x40
            // (see https://www.rfc-editor.org/rfc/rfc8949#name-major-types)
            uint8_t cbor[] = {0xD9, 0x9D, 0x75, 0x40, 0x00};
            size_t cbor_len = sizeof(cbor);
            if (share_len < 24) {
                cbor[3] |= (share_len & 0x1F);
                cbor_len--;
            } else {
                cbor[3] |= 0x18;
                cbor[4] = (uint8_t) share_len;
            }

            uint32_t checksum = 0;
            uint8_t checksum_len = sizeof(checksum);

            size_t cbor_share_crc_buffer_len = cbor_len + share_len + checksum_len;
            uint8_t cbor_share_crc_buffer[4 + SSKR_METADATA_LENGTH_BYTES + 1 +
                                          SSKR_MAX_STRENGTH_BYTES + 4];

            // sskr_words_buffer is space separated bytewords of cbor + share + checksum
            *share_words_buffer_length =
                ((cbor_len + share_len + checksum_len) * (SSKR_BYTEWORD_LENGTH + 1) - 1) *
                *share_count;

            for (uint8_t share = 0; share < *share_count; share++) {
                memcpy(cbor_share_crc_buffer, cbor, cbor_len);
                memcpy(cbor_share_crc_buffer + cbor_len,
                       share_hex_buffer + share_len * share,
                       share_len);
                checksum = crc32_nbo(cbor_share_crc_buffer, cbor_len + share_len);
                memcpy(cbor_share_crc_buffer + cbor_len + share_len, &checksum, checksum_len);

                if (bolos_ux_sskr_share_hex_decode(
                        cbor_share_crc_buffer,
                        cbor_share_crc_buffer_len,
                        share_words_buffer + share * (*share_words_buffer_length / *share_count),
                        *share_words_buffer_length / *share_count) < 1) {
                    memzero(share_hex_buffer, sizeof(share_hex_buffer));
                    memzero(cbor_share_crc_buffer, sizeof(cbor_share_crc_buffer));
                    memzero(share_words_buffer, sizeof(share_words_buffer));
                    share_words_buffer_length = 0;
                    memzero(bip39_words_buffer, sizeof(bip39_words_buffer));
                    return 0;
                }
                memzero(cbor_share_crc_buffer, sizeof(cbor_share_crc_buffer));
                checksum = 0;
            }
            memzero(share_hex_buffer, sizeof(share_hex_buffer));
        }
    }
    memzero(bip39_words_buffer, bip39_words_buffer_length);

    return 1;
}

unsigned int bolos_ux_sskr_hex_check(unsigned char *sskr_shares_hex,
                                     unsigned int sskr_shares_hex_length,
                                     unsigned int sskr_shares_count) {
    uint8_t cbor[] = {0xD9, 0x9D, 0x75};  // CBOR Tag #6.40309 is D9 9D75
    uint32_t checksum = 0;
    uint8_t checksum_len = sizeof(checksum);

    for (unsigned int i = 0; i < sskr_shares_count; i++) {
        checksum = crc32_nbo(sskr_shares_hex + i * (sskr_shares_hex_length / sskr_shares_count),
                             (sskr_shares_hex_length / sskr_shares_count) - checksum_len);
        // First 8 bytes of all shares in group should be same
        // Test checksum
        if ((os_secure_memcmp(cbor,
                              sskr_shares_hex + i * sskr_shares_hex_length / sskr_shares_count,
                              3) != 0) ||
            (i > 0 &&
             os_secure_memcmp(sskr_shares_hex,
                              sskr_shares_hex + i * sskr_shares_hex_length / sskr_shares_count,
                              8) != 0) ||
            (os_secure_memcmp(&checksum,
                              sskr_shares_hex +
                                  ((sskr_shares_hex_length / sskr_shares_count) * (i + 1)) -
                                  checksum_len,
                              checksum_len) != 0)) {
            memzero(sskr_shares_hex, sizeof(sskr_shares_hex));
            checksum = 0;
            return 0;
        };
        checksum = 0;
    }
    // hex encoded shares are OK
    return 1;
}

unsigned int bolos_ux_sskr_idx_strcpy(unsigned int index, unsigned char *buffer) {
    if (index < SSKR_WORDLIST_LENGTH / SSKR_BYTEWORD_LENGTH && buffer) {
        size_t word_length = SSKR_BYTEWORD_LENGTH;
        memcpy(buffer, SSKR_WORDLIST + SSKR_BYTEWORD_LENGTH * index, word_length);
        buffer[word_length] = 0;  // EOS
        return word_length;
    }
    // no word at that index
    // buffer[0] = 0; // EOS
    return 0;
}

unsigned int bolos_ux_sskr_get_word_idx_starting_with(const unsigned char *prefix,
                                                      const unsigned int prefixlength) {
    unsigned int i;
    for (i = 0; i < SSKR_WORDLIST_LENGTH / SSKR_BYTEWORD_LENGTH; i++) {
        unsigned int j = 0;
        while (j < (unsigned int) (SSKR_BYTEWORD_LENGTH) && j < prefixlength &&
               SSKR_WORDLIST[SSKR_BYTEWORD_LENGTH * i + j] == prefix[j]) {
            j++;
        }
        if (j == prefixlength) {
            return i;
        }
    }
    // no match, sry
    return SSKR_WORDLIST_LENGTH / SSKR_BYTEWORD_LENGTH;
}

unsigned int bolos_ux_sskr_get_word_count_starting_with(const unsigned char *prefix,
                                                        const unsigned int prefixlength) {
    unsigned int i;
    unsigned int count = 0;
    for (i = 0; i < SSKR_WORDLIST_LENGTH / SSKR_BYTEWORD_LENGTH; i++) {
        unsigned int j = 0;
        while (j < (unsigned int) (SSKR_BYTEWORD_LENGTH) && j < prefixlength &&
               SSKR_WORDLIST[SSKR_BYTEWORD_LENGTH * i + j] == prefix[j]) {
            j++;
        }
        if (j == prefixlength) {
            count++;
        }
        // don't seek till the end, abort when the prefix is not matched anymore
        else if (count > 0) {
            break;
        }
    }
    // return number of matched word starting with the given prefix
    return count;
}

// allocate at most 26 letters for next possibilities
// algorithm considers the SSKR words are alphabetically ordered in the wordlist
unsigned int bolos_ux_sskr_get_word_next_letters_starting_with(const unsigned char *prefix,
                                                               unsigned int prefixlength,
                                                               unsigned char *next_letters_buffer) {
    unsigned int i;
    unsigned int letter_count = 0;
    for (i = 0; i < SSKR_WORDLIST_LENGTH / SSKR_BYTEWORD_LENGTH; i++) {
        unsigned int j = 0;
        while (j < (unsigned int) (SSKR_BYTEWORD_LENGTH) && j < prefixlength &&
               SSKR_WORDLIST[SSKR_BYTEWORD_LENGTH * i + j] == prefix[j]) {
            j++;
        }
        if (j == prefixlength) {
            if (j < (unsigned int) (SSKR_BYTEWORD_LENGTH)) {
                // j is inc during previous loop, don't touch it
                unsigned char next_letter = SSKR_WORDLIST[SSKR_BYTEWORD_LENGTH * i + j];
                // add the first next_letter inconditionnally
                if (letter_count == 0) {
                    next_letters_buffer[0] = next_letter;
                    letter_count = 1;
                }
                // the next_letter is different
                else if (next_letters_buffer[0] != next_letter) {
                    next_letters_buffer++;
                    next_letters_buffer[0] = next_letter;
                    letter_count++;
                }
            }
        }
        // don't seek till the end, abort when the prefix is not matched anymore
        else if (letter_count > 0) {
            break;
        }
    }
    // return number of matched word starting with the given prefix
    return letter_count;
}

#if defined(HAVE_NBGL)
#include <nbgl_layout.h>

size_t bolos_ux_sskr_fill_with_candidates(const unsigned char *startingChars,
                                          const size_t startingCharsLength,
                                          char wordCandidatesBuffer[],
                                          const char *wordIndexorBuffer[]) {
    PRINTF("Calculating nb of words starting with '%s' (size is '%d')\n",
           startingChars,
           startingCharsLength);
    const size_t nbMatchingWords =
        MIN(bolos_ux_sskr_get_word_count_starting_with(startingChars, startingCharsLength),
            NB_MAX_SUGGESTION_BUTTONS);
    PRINTF("'%d' words start with '%s'\n", nbMatchingWords, startingChars);
    if (nbMatchingWords == 0) {
        return 0;
    }
    size_t matchingWordIndex =
        bolos_ux_sskr_get_word_idx_starting_with(startingChars, startingCharsLength);
    size_t offset = 0;
    for (size_t i = 0; i < nbMatchingWords; i++) {
        unsigned char *const wordDest = (unsigned char *) (&wordCandidatesBuffer[0] + offset);
        const size_t wordSize = bolos_ux_sskr_idx_strcpy(matchingWordIndex, wordDest);
        matchingWordIndex++;
        *(wordDest + wordSize) = '\0';
        offset += wordSize + 1;  // + trailing '\0' size
        wordIndexorBuffer[i] = (char *) wordDest;
    }
    return nbMatchingWords;
}

uint32_t bolos_ux_sskr_get_keyboard_mask(const unsigned char *prefix,
                                         const unsigned int prefixLength) {
    uint32_t existing_mask = 0;
    unsigned char next_letters[ALPHABET_LENGTH] = {0};
    PRINTF("Looking for letter candidates following '%s'\n", prefix);
    const size_t nb_letters =
        bolos_ux_sskr_get_word_next_letters_starting_with(prefix, prefixLength, next_letters);
    next_letters[nb_letters] = '\0';
    PRINTF("Next letters are in: %s\n", next_letters);
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        for (size_t j = 0; j < nb_letters; j++) {
            if (KBD_LETTERS[i] == next_letters[j]) {
                existing_mask += 1 << i;
            }
        }
    }
    return (-1 ^ existing_mask);
}
#endif
