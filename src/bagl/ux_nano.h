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

#include <ux.h>
#include "ui.h"
#include "../common/common.h"

#if defined(HAVE_BAGL)

typedef const bagl_element_t* (*keyboard_callback_t)(unsigned int event, unsigned int value);

void bolos_ux_hslider3_init(unsigned int total_count);
void bolos_ux_hslider3_set_current(unsigned int current);
void bolos_ux_hslider3_next(void);
void bolos_ux_hslider3_previous(void);

// all screens
void screen_onboarding_bip39_restore_init(void);
void screen_onboarding_sskr_restore_init(void);
void screen_onboarding_restore_word_init(unsigned int action);
void screen_onboarding_restore_word_display_auto_complete(void);

// bolos ux context (not mandatory if redesigning a bolos ux)
typedef struct bolos_ux_context {
    // 12, 18 or 24 word BIP39 onboarding kind
    unsigned int onboarding_kind;

    // Type of onboarding we are performing (BIP39 or SSKR)
    unsigned int onboarding_type;

    // State of the dynamic display
    unsigned int current_state;

#ifdef HAVE_ELECTRUM
    unsigned int onboarding_algorithm;
#endif  // HAVE_ELECTRUM

    unsigned int onboarding_step;
    unsigned int onboarding_index;
    unsigned int onboarding_words_checked;

    unsigned int words_buffer_length;

    // 128 of words (215 => hashed to 64, or 128) + HMAC_LENGTH*2 = 256
#define WORDS_BUFFER_MAX_SIZE_B 257
    char words_buffer[WORDS_BUFFER_MAX_SIZE_B];

    // after an int to make sure it's aligned
    char string_buffer[MAX(
        64,
        sizeof(bagl_icon_details_t) + BOLOS_APP_ICON_SIZE_B - 1)];  // to store the seed wholly

#if defined(TARGET_NANOX) || defined(TARGET_NANOS2)
    // label line for common PIN and common keyboard screen (displayed over the entry)
    const char* common_label;
#endif                      // defined(TARGET_NANOX) || defined(TARGET_NANOS2)
    char pin_digit_buffer;  // digit to be displayed

    appmain_t flow_end_callback;

    // slider management / menu list management
    unsigned int hslider3_before;
    unsigned int hslider3_current;
    unsigned int hslider3_after;
    unsigned int hslider3_total;

    keyboard_callback_t keyboard_callback;

    // for CheckSeed app only
    uint8_t processing;

#if defined(TARGET_NANOS)
    // 7 shares * 229 chars per share (46 SSKR Bytewords)
#define SSKR_WORDS_BUFFER_MAX_SIZE_B 1603
#else
    // 16 shares * 229 chars per share (46 SSKR Bytewords)
#define SSKR_WORDS_BUFFER_MAX_SIZE_B 3664
#endif
    uint8_t sskr_share_count;
    uint8_t sskr_share_index;
    unsigned int sskr_group_descriptor[1][2];
    unsigned int sskr_words_buffer_length;
    char sskr_words_buffer[SSKR_WORDS_BUFFER_MAX_SIZE_B];
} bolos_ux_context_t;

extern bolos_ux_context_t G_bolos_ux_context;

// update before, current, after index for horizontal slider with 3 positions
// slider distinguish handling from the data, to be more generic :)
#define BOLOS_UX_HSLIDER3_NONE (-1UL)

void screen_common_keyboard_init(unsigned int stack_slot,
                                 unsigned int current_element,
                                 unsigned int nb_elements,
                                 keyboard_callback_t callback);

void set_sskr_descriptor_values(void);
void recover_bip39(void);

#include "common/bip39/common_bip39.h"
#include "common/sskr/common_sskr.h"

void clean_exit(bolos_task_status_t exit_code);

#if defined(TARGET_NANOS)
#define BIP39_ICON                         C_bip39_nanos
#define SSKR_ICON                          C_sskr_nanos
#define PROCESSING_COMPLETE                0
#define PROCESSING_COMPARE_RECOVERY_PHRASE 1
#define PROCESSING_GENERATE_SSKR           2

extern const bagl_element_t screen_onboarding_word_list_elements[9];
void compare_recovery_phrase_and_display_result(void);
void generate_sskr(void);
void screen_processing_init(void);
#else
#define BIP39_ICON C_bip39_nanox
#define SSKR_ICON  C_sskr_nanox

// to be included into all flow that needs to go back to the dashboard
extern const ux_flow_step_t ux_ob_goto_dashboard_step;
#endif  // defined(TARGET_NANOS)

#endif  // defined(HAVE_BAGL)
