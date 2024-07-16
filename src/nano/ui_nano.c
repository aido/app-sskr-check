#include <ux.h>
#include "ui.h"

#if defined(HAVE_BAGL)

#include "constants.h"

enum UI_STATE { UI_IDLE, UI_TEXT, UI_APPROVAL };

enum UI_STATE uiState;

ux_state_t G_ux;

//////////////////////////////////////////////////////////////////////

void screen_onboarding_bip39_restore_init(void) {
    G_bolos_ux_context.onboarding_type = ONBOARDING_TYPE_BIP39;
    screen_onboarding_restore_word_init(RESTORE_WORD_ACTION_FIRST_WORD);
}

const char* const number_of_bip39_words_values[] = {
    "12 words",
    "18 words",
    "24 words",
    "Back",
};

const char* number_of_bip39_words_getter(unsigned int idx) {
    if (idx < ARRAYLEN(number_of_bip39_words_values)) {
        return number_of_bip39_words_values[idx];
    }
    return NULL;
}

void number_of_bip39_words_selector(unsigned int idx) {
    switch (idx) {
        case 0:
            G_bolos_ux_context.onboarding_kind = BIP39_MNEMONIC_SIZE_12;
            goto word_init;
        case 1:
            G_bolos_ux_context.onboarding_kind = BIP39_MNEMONIC_SIZE_18;
            goto word_init;
        case 2:
            G_bolos_ux_context.onboarding_kind = BIP39_MNEMONIC_SIZE_24;
            goto word_init;
        word_init:
            screen_onboarding_bip39_restore_init();
            break;
        default:
            ui_idle_init();
    }
}

#if defined(TARGET_NANOS)
UX_STEP_NOCB(ux_bip39_instruction_step, nn, {"Enter number", "of BIP39 words"});
#elif defined(TARGET_NANOX) || defined(TARGET_NANOS2)
UX_STEP_NOCB(ux_bip39_instruction_step,
             nnn,
             {
                 "Select the number of",
                 "words written on",
                 "your Recovery Sheet",
             });
#endif

UX_STEP_MENULIST(ux_bip39_menu_step, number_of_bip39_words_getter, number_of_bip39_words_selector);

UX_FLOW(ux_bip39_flow, &ux_bip39_instruction_step, &ux_bip39_menu_step);

//////////////////////////////////////////////////////////////////////

void screen_onboarding_sskr_restore_init(void) {
    G_bolos_ux_context.onboarding_type = ONBOARDING_TYPE_SSKR;
    screen_onboarding_restore_word_init(RESTORE_WORD_ACTION_FIRST_WORD);
}

#if defined(TARGET_NANOS)
UX_STEP_CB(ux_sskr_instruction_step,
           nn,
           screen_onboarding_sskr_restore_init(),
           {
               "Enter SSKR",
               "recovery phrase",
           });
#elif defined(TARGET_NANOX) || defined(TARGET_NANOS2)
UX_STEP_CB(ux_sskr_instruction_step, nnn, G_bolos_ux_context.onboarding_type = ONBOARDING_TYPE_SSKR;
           screen_onboarding_restore_word_init(RESTORE_WORD_ACTION_FIRST_WORD);
           ,
           {
               "Enter first word of",
               "first share of SSKR",
               "recovery phrase",
           });
#endif

UX_FLOW(ux_sskr_flow, &ux_sskr_instruction_step);

//////////////////////////////////////////////////////////////////////

UX_STEP_VALID(ux_idle_flow_1_step,
              pbb,
              ux_flow_init(0, ux_bip39_flow, NULL),
              {
                  &BIP39_ICON,
                  "Check BIP39",
                  "recovery phrase",
              });
UX_STEP_VALID(ux_idle_flow_2_step,
              pbb,
              ux_flow_init(0, ux_sskr_flow, NULL),
              {
                  &SSKR_ICON,
                  "Check SSKR",
                  "recovery phrase",
              });

UX_STEP_NOCB(ux_idle_flow_3_step,
             bn,
             {
                 "Version",
                 APPVERSION,
             });
UX_STEP_VALID(ux_idle_flow_4_step,
              pb,
              os_sched_exit(-1),
              {
                  &C_icon_dashboard_x,
                  "Quit",
              });
UX_FLOW(ux_idle_flow,
        &ux_idle_flow_1_step,
        &ux_idle_flow_2_step,
        &ux_idle_flow_3_step,
        &ux_idle_flow_4_step);

void ui_idle_init(void) {
    uiState = UI_IDLE;

    memzero(G_bolos_ux_context.words_buffer, sizeof(G_bolos_ux_context.words_buffer));
    memzero(G_bolos_ux_context.string_buffer, sizeof(G_bolos_ux_context.string_buffer));
    memzero(G_bolos_ux_context.sskr_words_buffer, G_bolos_ux_context.sskr_words_buffer_length);
    G_bolos_ux_context.words_buffer_length = 0;
    G_bolos_ux_context.sskr_words_buffer_length = 0;
    G_bolos_ux_context.sskr_share_index = 0;

    // reserve a display stack slot if none yet
    if (G_ux.stack_count == 0) {
        ux_stack_push();
    }
    ux_flow_init(0, ux_idle_flow, NULL);
}

#endif
