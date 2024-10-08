/*******************************************************************************
 *   Ledger Blue - Secure firmware
 *   (c) 2016, 2017 Ledger
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

#include "ux_nano.h"

#if defined(HAVE_BAGL)

bolos_ux_context_t G_bolos_ux_context;

void clean_exit(bolos_task_status_t exit_code) {
    memzero(G_bolos_ux_context.words_buffer, sizeof(G_bolos_ux_context.words_buffer));
    memzero(G_bolos_ux_context.string_buffer, sizeof(G_bolos_ux_context.string_buffer));
    memzero(G_bolos_ux_context.sskr_words_buffer, G_bolos_ux_context.sskr_words_buffer_length);
    G_bolos_ux_context.words_buffer_length = 0;
    G_bolos_ux_context.sskr_words_buffer_length = 0;
    G_bolos_ux_context.sskr_share_index = 0;

    os_sched_exit(exit_code);
}

unsigned short io_timeout(unsigned short last_timeout) {
    UNUSED(last_timeout);
    // infinite timeout
    return 1;
}

void io_seproxyhal_display(const bagl_element_t *element) {
    io_seproxyhal_display_default((bagl_element_t *) element);
}

void bolos_ux_hslider3_init(unsigned int total_count) {
    G_bolos_ux_context.hslider3_total = total_count;
    switch (total_count) {
        case 0:
            G_bolos_ux_context.hslider3_before = BOLOS_UX_HSLIDER3_NONE;
            G_bolos_ux_context.hslider3_current = BOLOS_UX_HSLIDER3_NONE;
            G_bolos_ux_context.hslider3_after = BOLOS_UX_HSLIDER3_NONE;
            break;
        case 1:
            G_bolos_ux_context.hslider3_before = BOLOS_UX_HSLIDER3_NONE;
            G_bolos_ux_context.hslider3_current = 0;
            G_bolos_ux_context.hslider3_after = BOLOS_UX_HSLIDER3_NONE;
            break;
        case 2:
            G_bolos_ux_context.hslider3_before = BOLOS_UX_HSLIDER3_NONE;
            // G_bolos_ux_context.hslider3_before = 1; // full rotate
            G_bolos_ux_context.hslider3_current = 0;
            G_bolos_ux_context.hslider3_after = 1;
            break;
        default:
            G_bolos_ux_context.hslider3_before = total_count - 1;
            G_bolos_ux_context.hslider3_current = 0;
            G_bolos_ux_context.hslider3_after = 1;
            break;
    }
}

void bolos_ux_hslider3_set_current(unsigned int current) {
    // index is reachable ?
    if (G_bolos_ux_context.hslider3_total > current) {
        // reach it
        while (G_bolos_ux_context.hslider3_current != current) {
            bolos_ux_hslider3_next();
        }
    }
}

void bolos_ux_hslider3_next(void) {
    switch (G_bolos_ux_context.hslider3_total) {
        case 0:
        case 1:
            break;
        case 2:
            switch (G_bolos_ux_context.hslider3_current) {
                case 0:
                    G_bolos_ux_context.hslider3_before = 0;
                    G_bolos_ux_context.hslider3_current = 1;
                    G_bolos_ux_context.hslider3_after = BOLOS_UX_HSLIDER3_NONE;
                    break;
                case 1:
                    G_bolos_ux_context.hslider3_before = BOLOS_UX_HSLIDER3_NONE;
                    G_bolos_ux_context.hslider3_current = 0;
                    G_bolos_ux_context.hslider3_after = 1;
                    break;
            }
            break;
        default:
            G_bolos_ux_context.hslider3_before = G_bolos_ux_context.hslider3_current;
            G_bolos_ux_context.hslider3_current = G_bolos_ux_context.hslider3_after;
            G_bolos_ux_context.hslider3_after =
                (G_bolos_ux_context.hslider3_after + 1) % G_bolos_ux_context.hslider3_total;
            break;
    }
}

void bolos_ux_hslider3_previous(void) {
    switch (G_bolos_ux_context.hslider3_total) {
        case 0:
        case 1:
            break;
        case 2:
            switch (G_bolos_ux_context.hslider3_current) {
                case 0:
                    G_bolos_ux_context.hslider3_before = 0;
                    G_bolos_ux_context.hslider3_current = 1;
                    G_bolos_ux_context.hslider3_after = BOLOS_UX_HSLIDER3_NONE;
                    break;
                case 1:
                    G_bolos_ux_context.hslider3_before = BOLOS_UX_HSLIDER3_NONE;
                    G_bolos_ux_context.hslider3_current = 0;
                    G_bolos_ux_context.hslider3_after = 1;
                    break;
            }
            break;
        default:
            G_bolos_ux_context.hslider3_after = G_bolos_ux_context.hslider3_current;
            G_bolos_ux_context.hslider3_current = G_bolos_ux_context.hslider3_before;
            G_bolos_ux_context.hslider3_before =
                (G_bolos_ux_context.hslider3_before + G_bolos_ux_context.hslider3_total - 1) %
                G_bolos_ux_context.hslider3_total;
            break;
    }
}

UX_STEP_CB(ux_restore_step_1, nn, screen_onboarding_restore_word_display_auto_complete();
           , {"Enter", G_ux.string_buffer});

UX_FLOW(ux_restore_flow, &ux_restore_step_1);

UX_STEP_CB(ux_quit_step, pb, clean_exit(0), {&C_icon_dashboard_x, "Quit"});
UX_STEP_VALID(ux_return_step, pb, ui_idle_init(), {&C_icon_back_x, "Return to menu"});
UX_STEP_NOCB(ux_invalid_step_2,
             nn,
             {
                 "Check length,",
                 "order and spelling",
             });

UX_STEP_NOCB(ux_bip39_invalid_step_1, pbb, {&C_icon_crossmark, "BIP39 Recovery", "phrase invalid"});
UX_STEP_VALID(ux_bip39_invalid_step_3, pb, screen_onboarding_bip39_restore_init();
              , {&C_icon_back_x, "Re-enter phrase"});

UX_FLOW(ux_bip39_invalid_flow,
        &ux_bip39_invalid_step_1,
        &ux_invalid_step_2,
        &ux_bip39_invalid_step_3,
        &ux_return_step);

UX_STEP_NOCB(ux_bip39_nomatch_step_1, pbb, {&C_icon_warning, "BIP39 Phrase", "doesn't match"});

UX_FLOW(ux_bip39_nomatch_flow, &ux_bip39_nomatch_step_1, &ux_return_step);

UX_STEP_NOCB(ux_bip39_match_step_1, pbb, {&C_icon_validate_14, "BIP39 Phrase", "is correct"});
UX_STEP_CB(ux_bip39_recover_step_1, pbb, set_sskr_descriptor_values();
           , {&SSKR_ICON, "Generate", "SSKR phrases"});

UX_FLOW(ux_bip39_match_flow, &ux_bip39_match_step_1, &ux_quit_step, &ux_bip39_recover_step_1);

UX_STEP_NOCB(ux_sskr_invalid_step_1, pbb, {&C_icon_crossmark, "SSKR Recovery", "phrase invalid"});
UX_STEP_VALID(ux_sskr_invalid_step_3, pb, screen_onboarding_sskr_restore_init();
              , {&C_icon_back_x, "Re-enter shares"});

UX_FLOW(ux_sskr_invalid_flow,
        &ux_sskr_invalid_step_1,
        &ux_invalid_step_2,
        &ux_sskr_invalid_step_3,
        &ux_return_step);

UX_STEP_NOCB(ux_sskr_nomatch_step_1, pbb, {&C_icon_warning, "SSKR Phrase", "doesn't match"});

UX_STEP_NOCB(ux_sskr_match_step_1, pbb, {&C_icon_validate_14, "SSKR Phrase", "is correct"});

UX_STEP_CB(ux_sskr_recover_step_1, pbb, recover_bip39();, {&BIP39_ICON, "Recover", "BIP39 phrase"});

UX_FLOW(ux_sskr_nomatch_flow, &ux_sskr_nomatch_step_1, &ux_quit_step, &ux_sskr_recover_step_1);

UX_FLOW(ux_sskr_match_flow, &ux_sskr_match_step_1, &ux_quit_step, &ux_sskr_recover_step_1);
#endif  // defined(HAVE_BAGL)
