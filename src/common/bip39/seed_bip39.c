/* @BANNER@ */

#include <os.h>
#include <cx.h>

#include "../common.h"
#include "./seed_rom_variables.h"

// separated function to lower the stack usage when jumping into pbkdf algorithm
unsigned int bolos_ux_bip39_mnemonic_to_seed_hash_length128(unsigned char* mnemonic,
                                                            unsigned int mnemonic_length) {
    if (mnemonic_length > 128) {
        cx_hash_sha512(mnemonic, mnemonic_length, mnemonic, 64);
        // new mnemonic length
        mnemonic_length = 64;
    }
    return mnemonic_length;
}

void bolos_ux_bip39_mnemonic_to_seed(unsigned char* mnemonic,
                                     unsigned int mnemonic_length,
                                     unsigned char* seed) {
    // Need to keep BIP39 mnemonic in case we want to generate SSKR from it
    // It will be zeroed later if not needed
    unsigned char mnemonic_hash[257];
    memcpy(mnemonic_hash, mnemonic, mnemonic_length);
    unsigned char passphrase[BIP39_MNEMONIC_LENGTH + 4];
    mnemonic_length =
        bolos_ux_bip39_mnemonic_to_seed_hash_length128(mnemonic_hash, mnemonic_length);
    memcpy(passphrase, BIP39_MNEMONIC, BIP39_MNEMONIC_LENGTH);
    cx_pbkdf2_sha512(mnemonic_hash,
                     mnemonic_length,
                     passphrase,
                     BIP39_MNEMONIC_LENGTH,
                     BIP39_PBKDF2_ROUNDS,
                     seed,
                     64);
    memzero(mnemonic_hash, sizeof(mnemonic_hash));
    PRINTF("BIP39 seed:\n %.*H\n", 64, seed);
}

unsigned int bolos_ux_bip39_mnemonic_decode(unsigned char* mnemonic,
                                            unsigned int mnemonic_length,
                                            unsigned char* bits,
                                            unsigned int bitslength) {
    unsigned int i, n = 0;
    unsigned int bi;
    unsigned char buffer[32];
    unsigned char mask;

    PRINTF("BIP39 mnemonic phrase:\n %.*s\n", mnemonic_length, mnemonic);

    for (i = 0; i < mnemonic_length; i++) {
        if (mnemonic[i] == ' ') {
            n++;
        }
    }
    n++;
    if (n != 12 && n != 18 && n != 24) {
        return 0;
    }
    memzero(bits, bitslength);
    i = 0;
    bi = 0;
    while (i < mnemonic_length) {
        unsigned char current_word[10];
        unsigned int current_word_size = 0;
        unsigned int j, k, ki;
        j = 0;
        while (i < mnemonic_length && mnemonic[i] != ' ') {
            if (j >= sizeof(current_word)) {
                memzero(bits, bitslength);
                return 0;
            }
            current_word[j] = mnemonic[i];
            current_word_size = j;
            i++;
            j++;
        }
        if (i < mnemonic_length) {
            i++;
        }
        current_word_size++;
        for (k = 0; k < BIP39_WORDLIST_OFFSETS_LENGTH - 1; k++) {
            if ((os_secure_memcmp(current_word,
                                  (void*) (BIP39_WORDLIST + BIP39_WORDLIST_OFFSETS[k]),
                                  current_word_size) == 0) &&
                ((unsigned int) (BIP39_WORDLIST_OFFSETS[k + 1] - BIP39_WORDLIST_OFFSETS[k]) ==
                 current_word_size)) {
                for (ki = 0; ki < 11; ki++) {
                    if (k & (1 << (10 - ki))) {
                        bits[bi / 8] |= 1 << (7 - (bi % 8));
                    }
                    bi++;
                }
                break;
            }
        }
        if (k == (unsigned int) (BIP39_WORDLIST_OFFSETS_LENGTH - 1)) {
            memzero(bits, bitslength);
            return 0;
        }
    }
    if (bi != n * 11) {
        memzero(bits, bitslength);
        return 0;
    }

    cx_hash_sha256(bits, n * 4 / 3, buffer, 32);
    switch (n) {
        case 12:
            mask = 0xF0;
            break;
        case 18:
            mask = 0xFC;
            break;
        default:
            mask = 0xFF;
            break;
    }
    if ((buffer[0] & mask) != (bits[n * 4 / 3] & mask)) {
        memzero(bits, bitslength);
        return 0;
    }

    // alright mnemonic is ok
    PRINTF("BIP39 mnemonic decoded in hex:\n %.*H\n", bitslength, bits);
    return 1;
}

unsigned int bolos_ux_bip39_mnemonic_encode(const uint8_t* seed,
                                            uint8_t seed_len,
                                            char* out,
                                            size_t out_len) {
    if (seed_len % 4 || seed_len < 16 || seed_len > 32) {
        return 0;
    }
    uint8_t bits[32 + 1];
    cx_hash_sha256(seed, seed_len, bits, 32);

    // checksum
    bits[seed_len] = bits[0];
    // data
    memcpy(bits, seed, seed_len);

    unsigned int i, j, idx;
    unsigned int offset = 0;
    for (i = 0; i < (seed_len * 3 / 4); i++) {
        uint8_t word_len;
        idx = 0;
        for (j = 0; j < 11; j++) {
            idx <<= 1;
            idx += (bits[(i * 11 + j) / 8] & (1 << (7 - ((i * 11 + j) % 8)))) != 0;
        }
        word_len = BIP39_WORDLIST_OFFSETS[idx + 1] - BIP39_WORDLIST_OFFSETS[idx];
        if ((offset + word_len) > out_len) {
            memzero(bits, sizeof(bits));
            return 0;
        }
        memcpy(out + offset, BIP39_WORDLIST + BIP39_WORDLIST_OFFSETS[idx], word_len);
        offset += word_len;
        if (offset > out_len) {
            memzero(bits, sizeof(bits));
            return 0;
        }
        if (i < (seed_len * 3 / 4) - 1) {
            out[offset++] = ' ';
        }
    }
    memzero(bits, sizeof(bits));

    PRINTF("BIP39 encoded mnemonic:\n %.*s\n", offset, out);
    return offset;
}

unsigned int bolos_ux_bip39_mnemonic_check(unsigned char* mnemonic, unsigned int mnemonic_length) {
    unsigned char bits[32 + 1];

    if (bolos_ux_bip39_mnemonic_decode(mnemonic, mnemonic_length, bits, 32 + 1) != 1) {
        memzero(bits, 32 + 1);
        return 0;
    }
    memzero(bits, 32 + 1);

    // alright mnemonic is ok
    return 1;
}

unsigned int bolos_ux_bip39_idx_strcpy(unsigned int index, unsigned char* buffer) {
    if (index < BIP39_WORDLIST_OFFSETS_LENGTH - 1 && buffer) {
        size_t word_length = BIP39_WORDLIST_OFFSETS[index + 1] - BIP39_WORDLIST_OFFSETS[index];
        memcpy(buffer, BIP39_WORDLIST + BIP39_WORDLIST_OFFSETS[index], word_length);
        buffer[word_length] = 0;  // EOS
        return word_length;
    }
    // no word at that index
    // buffer[0] = 0; // EOS
    return 0;
}

unsigned int bolos_ux_bip39_get_word_idx_starting_with(const unsigned char* prefix,
                                                       const unsigned int prefixlength) {
    unsigned int i;
    for (i = 0; i < BIP39_WORDLIST_OFFSETS_LENGTH - 1; i++) {
        unsigned int j = 0;
        while (j < (unsigned int) (BIP39_WORDLIST_OFFSETS[i + 1] - BIP39_WORDLIST_OFFSETS[i]) &&
               j < prefixlength && BIP39_WORDLIST[BIP39_WORDLIST_OFFSETS[i] + j] == prefix[j]) {
            j++;
        }
        if (j == prefixlength) {
            return i;
        }
    }
    // no match, sry
    return BIP39_WORDLIST_OFFSETS_LENGTH;
}

unsigned int bolos_ux_bip39_get_word_count_starting_with(const unsigned char* prefix,
                                                         const unsigned int prefixlength) {
    unsigned int i;
    unsigned int count = 0;
    for (i = 0; i < BIP39_WORDLIST_OFFSETS_LENGTH - 1; i++) {
        unsigned int j = 0;
        while (j < (unsigned int) (BIP39_WORDLIST_OFFSETS[i + 1] - BIP39_WORDLIST_OFFSETS[i]) &&
               j < prefixlength && BIP39_WORDLIST[BIP39_WORDLIST_OFFSETS[i] + j] == prefix[j]) {
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
// algorithm considers the bip39 words are alphabetically ordered in the wordlist
unsigned int bolos_ux_bip39_get_word_next_letters_starting_with(
    const unsigned char* prefix,
    const unsigned int prefixlength,
    unsigned char* next_letters_buffer) {
    unsigned int i;
    unsigned int letter_count = 0;
    for (i = 0; i < BIP39_WORDLIST_OFFSETS_LENGTH - 1; i++) {
        unsigned int j = 0;
        while (j < (unsigned int) (BIP39_WORDLIST_OFFSETS[i + 1] - BIP39_WORDLIST_OFFSETS[i]) &&
               j < prefixlength && BIP39_WORDLIST[BIP39_WORDLIST_OFFSETS[i] + j] == prefix[j]) {
            j++;
        }
        if (j == prefixlength) {
            if (j < (unsigned int) (BIP39_WORDLIST_OFFSETS[i + 1] - BIP39_WORDLIST_OFFSETS[i])) {
                // j is inc during previous loop, don't touch it
                unsigned char next_letter = BIP39_WORDLIST[BIP39_WORDLIST_OFFSETS[i] + j];
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

size_t bolos_ux_bip39_fill_with_candidates(const unsigned char* startingChars,
                                           const size_t startingCharsLength,
                                           char wordCandidatesBuffer[],
                                           const char* wordIndexorBuffer[]) {
    PRINTF("Calculating nb of words starting with '%s' (size is '%d')\n",
           startingChars,
           startingCharsLength);
    const size_t nbMatchingWords =
        MIN(bolos_ux_bip39_get_word_count_starting_with(startingChars, startingCharsLength),
            NB_MAX_SUGGESTION_BUTTONS);
    PRINTF("'%d' words start with '%s'\n", nbMatchingWords, startingChars);
    if (nbMatchingWords == 0) {
        return 0;
    }
    size_t matchingWordIndex =
        bolos_ux_bip39_get_word_idx_starting_with(startingChars, startingCharsLength);
    size_t offset = 0;
    for (size_t i = 0; i < nbMatchingWords; i++) {
        unsigned char* const wordDest = (unsigned char*) (&wordCandidatesBuffer[0] + offset);
        const size_t wordSize = bolos_ux_bip39_idx_strcpy(matchingWordIndex, wordDest);
        matchingWordIndex++;
        *(wordDest + wordSize) = '\0';
        offset += wordSize + 1;  // + trailing '\0' size
        wordIndexorBuffer[i] = (char*) wordDest;
    }
    return nbMatchingWords;
}

uint32_t bolos_ux_bip39_get_keyboard_mask(const unsigned char* prefix,
                                          const unsigned int prefixLength) {
    uint32_t existing_mask = 1 << 28;  // Starting with the 'return' keypad activated
    unsigned char next_letters[ALPHABET_LENGTH] = {0};
    PRINTF("Looking for letter candidates following '%s'\n", prefix);
    const size_t nb_letters =
        bolos_ux_bip39_get_word_next_letters_starting_with(prefix, prefixLength, next_letters);
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
