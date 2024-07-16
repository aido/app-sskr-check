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

#define ONBOARDING_WORD_COMPLETION_MAX_ITEMS 8
#define BOLOS_UX_HASH_LENGTH                 4  // as on the blue

#define BIP39_MAX_WORD_LENGTH 8
#define MAX_NUMBER_LENGTH     2

enum {
    BIP39_MNEMONIC_SIZE_12 = 12,
    BIP39_MNEMONIC_SIZE_18 = 18,
    BIP39_MNEMONIC_SIZE_24 = 24,
};

// Type of onboarding we are performing (BIP39 or SSKR)
enum { ONBOARDING_TYPE_BIP39, ONBOARDING_TYPE_SSKR };

// State of the dynamic display
enum { STATIC_SCREEN, DYNAMIC_SCREEN };

#define KEYBOARD_ITEM_VALIDATED \
    1  // callback is called with the entered item index, tmp_element is precharged with element to
       // be displayed and using the common string buffer as string parameter
#define KEYBOARD_RENDER_ITEM \
    2  // callback is called with the element index, tmp_element is precharged with element to be
       // displayed and using the common string buffer as string parameter
#define KEYBOARD_RENDER_WORD \
    3  // callback is called with a -1 when requesting complete word, or the char index else,
       // returning 0 implies no char is to be displayed

#define RESTORE_WORD_ACTION_REENTER_WORD 0
#define RESTORE_WORD_ACTION_FIRST_WORD   1

#define COMMON_KEYBOARD_INDEX_UNCHANGED (-1UL)
