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

#define memzero(...) explicit_bzero(__VA_ARGS__)

#define ALPHABET_LENGTH 27
#define KBD_LETTERS     "qwertyuiopasdfghjklzxcvbnm"

#define BIP39_WORDLIST_LENGTH         11068
#define BIP39_WORDLIST_OFFSETS_LENGTH 2049
#define BIP39_MNEMONIC_LENGTH         8

#define SSKR_WORDLIST_LENGTH 1024
#define SSKR_BYTEWORD_LENGTH 4

#ifdef HAVE_ELECTRUM

#define ELECTRUM_SEED_VERSION_LENGTH  12
#define ELECTRUM_MNEMONIC_LENGTH      8
#define ELECTRUM_SEED_PREFIX_STANDARD 0x01
#define ELECTRUM_PBKDF2_ROUNDS        2048

#endif

#define BIP39_PBKDF2_ROUNDS 2048

extern unsigned char const WIDE BIP39_WORDLIST[BIP39_WORDLIST_LENGTH];
extern unsigned short const WIDE BIP39_WORDLIST_OFFSETS[BIP39_WORDLIST_OFFSETS_LENGTH];
extern unsigned char const WIDE BIP39_MNEMONIC[BIP39_MNEMONIC_LENGTH];

extern unsigned char const WIDE SSKR_WORDLIST[SSKR_WORDLIST_LENGTH];
extern unsigned short const WIDE SSKR_WORDLIST_OFFSET;
extern unsigned char const WIDE SSKR_BYTEWORD[SSKR_BYTEWORD_LENGTH];

#ifdef HAVE_ELECTRUM

extern unsigned char const WIDE ELECTRUM_SEED_VERSION[ELECTRUM_SEED_VERSION_LENGTH];
extern unsigned char const WIDE ELECTRUM_MNEMONIC[ELECTRUM_MNEMONIC_LENGTH];

#endif
