/*******************************************************************************
 *   (c) 2016-2022 Ledger SAS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#ifdef HAVE_ELECTRUM

#include "common.h"

int cx_math_shiftr_11(unsigned char *r, unsigned int len) {
    unsigned int j, b11;
    b11 = r[len - 1] | ((r[len - 2] & 7) << 8);

    for (j = len - 2; j > 0; j--) {
        r[j + 1] = (r[j] >> 3) | (r[j - 1] << 5);
    }
    r[1] = r[0] >> 3;
    r[0] = 0;

    return b11;
}

static unsigned int bolos_ux_electrum_bip39_mnemonic_encode(const uint8_t *seed17,
                                                            uint8_t *out,
                                                            size_t out_length) {
    unsigned char tmp[17];
    unsigned int i;
    unsigned int offset = 0;
    memcpy(tmp, seed17, sizeof(tmp));
    for (i = 0; i < 12; i++) {
        unsigned char word_length;
        unsigned int idx = cx_math_shiftr_11(tmp, sizeof(tmp));
        word_length = BIP39_WORDLIST_OFFSETS[idx + 1] - BIP39_WORDLIST_OFFSETS[idx];
        if ((offset + word_length) > out_length) {
            THROW(INVALID_PARAMETER);
        }
        memcpy(out + offset, BIP39_WORDLIST + BIP39_WORDLIST_OFFSETS[idx], word_length);
        offset += word_length;
        if (i < 11) {
            if (offset > out_length) {
                THROW(INVALID_PARAMETER);
            }
            out[offset++] = ' ';
        }
    }
    return offset;
}

unsigned int bolos_ux_electrum_new_bip39_mnemonic(unsigned int version,
                                                  unsigned char *out,
                                                  unsigned int out_length) {
    unsigned char seed[17];
    unsigned int nonce;
    unsigned int offset;
    // Initialize a proper seed <= 132 bits
    for (;;) {
        cx_rng(seed, sizeof(seed));
        if (seed[0] < 0x10) {
            break;
        }
    }
    nonce = (seed[sizeof(seed) - 4] << 24) | (seed[sizeof(seed) - 3] << 16) |
            (seed[sizeof(seed) - 2] << 8) | (seed[sizeof(seed) - 1]);
    // Find a nonce that matches the version
    for (;;) {
        nonce++;
        seed[sizeof(seed) - 4] = (nonce >> 24);
        seed[sizeof(seed) - 3] = (nonce >> 16);
        seed[sizeof(seed) - 2] = (nonce >> 8);
        seed[sizeof(seed) - 1] = nonce;
        offset = bolos_ux_electrum_bip39_mnemonic_encode(seed, out, out_length);
        if (bolos_ux_electrum_bip39_mnemonic_check(version, out, offset)) {
            break;
        }
    }
    return offset;
}

unsigned int bolos_ux_electrum_bip39_mnemonic_check(unsigned int version,
                                                    unsigned char *mnemonic,
                                                    unsigned int mnemonic_length) {
    unsigned char tmp[64];
    cx_hmac_sha512(ELECTRUM_SEED_VERSION,
                   ELECTRUM_SEED_VERSION_LENGTH,
                   mnemonic,
                   mnemonic_length,
                   tmp,
                   64);
    return (tmp[0] == version);
}

#endif
