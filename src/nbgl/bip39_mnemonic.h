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

#pragma once

#include <stdbool.h>
#include "constants.h"

#if defined(SCREEN_SIZE_WALLET)

#define BIP39_MNEMONIC_MAX_LENGTH (BIP39_MNEMONIC_SIZE_24 * (BIP39_MAX_WORD_LENGTH + 1))

/*
 * Sets how many words are expected in the mnemonic passphrase
 */
void bip39_mnemonic_final_size_set(const size_t size);

/*
 * Returns how many words are expected in the mnemonic passphrase
 */
size_t bip39_mnemonic_final_size_get(void);

/*
 * Returns how many words are currently stored in the mnemonic
 */
size_t bip39_mnemonic_current_word_number_get(void);

/*
 * Check if the current number of words in the mnemonic fits the expected number of words
 */
bool bip39_mnemonic_complete_check(void);

/*
 * Check if the currently stored mnemonic generates the same seed as the current device's one
 */
bool bip39_mnemonic_check(bool* match);

/*
 * Erase all information and reset the indexes
 */
void bip39_mnemonic_reset(void);

/*
 * Remove the latest word from the passphrase, returns true if there was at least one to remove,
 * else false (there was no word)
 */
bool bip39_mnemonic_word_remove(void);

/*
 * Adds a word in the passphrase, returns how many words are stored in the mnemonic
 */
size_t bip39_mnemonic_word_add(const char* const buffer, const size_t size);

/*
 * Generate BIP39 mnemonic from SSKR shares
 */
void bip39_mnemonic_from_sskr_shares(unsigned char* seed);

/*
 * Returns the mnemonic passphrase
 */
char* bip39_mnemonic_get(void);

/*
 * Returns length of the mnemonic passphrase
 */
size_t bip39_mnemonic_length_get(void);

#endif  // SCREEN_SIZE_WALLET
