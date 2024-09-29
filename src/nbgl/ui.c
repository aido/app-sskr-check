#include <string.h>
#include <os.h>

#include "constants.h"
#include "glyphs.h"

#if defined(HAVE_NBGL)

#include <nbgl_use_case.h>
#include <nbgl_fonts.h>
#include <nbgl_front.h>
#include <nbgl_debug.h>
#include <nbgl_page.h>
#include <nbgl_layout.h>

#include "../common/bip39/common_bip39.h"
#include "../common/sskr/common_sskr.h"
#include "../ui.h"
#include "./bip39_mnemonic.h"
#include "./sskr_shares.h"
#include "./layout_generic_screen.h"

#define HEADER_SIZE 50

static nbgl_page_t *pageContext;

static char headerText[HEADER_SIZE] = {0};
static nbgl_layout_t *layout = 0;

unsigned int onboarding_type;

static void display_home_page(void);
static void display_check_keyboard_page(void);
static void display_check_result_page(const bool result);
static void display_bip39_select_phrase_length_page(void);
static void display_bip39_mnemonic(void);
static void display_sskr_select_numshares_page(void);
static void display_sskr_select_threshold_page(void);

/*
 * Utils
 */
static const char *buttonTexts[NB_MAX_SUGGESTION_BUTTONS] = {0};

static void reset_globals() {
    bip39_mnemonic_reset();
    sskr_shares_reset();
    memzero(buttonTexts, sizeof(buttonTexts[0]) * NB_MAX_SUGGESTION_BUTTONS);
}

static void on_quit(void) {
    os_sched_exit(-1);
}

/*
 * Select tool type, BIP39 or SSKR
 */
enum select_tool {
    SELECT_TOOL_ICON_INDEX = 0,
    SELECT_TOOL_TEXT_INDEX,
    SELECT_TOOL_BIP39_INDEX,
    SELECT_TOOL_SSKR_INDEX,
    SELECT_TOOL_BIP85_INDEX,
    SELECT_TOOL_BACK_BUTTON_INDEX,
    SELECT_TOOL_NB_CHILDREN
};

#define SELECT_TOOL_NB_BUTTONS 3

static const char *toolType[] = {"BIP39 Check", "SSKR Check", "BIP85 Generate"};
static void select_tool_callback(nbgl_obj_t *obj, nbgl_touchType_t eventType) {
    nbgl_obj_t **screenChildren = nbgl_screenGetElements(0);
    if (eventType != TOUCHED) {
        return;
    }
    io_seproxyhal_play_tune(TUNE_TAP_CASUAL);
    if (obj == screenChildren[SELECT_TOOL_BIP39_INDEX]) {
        nbgl_layoutRelease(layout);
        onboarding_type = ONBOARDING_TYPE_BIP39;
        display_bip39_select_phrase_length_page();
    } else if (obj == screenChildren[SELECT_TOOL_SSKR_INDEX]) {
        nbgl_layoutRelease(layout);
        onboarding_type = ONBOARDING_TYPE_SSKR;
        display_check_keyboard_page();
    } else if (obj == screenChildren[SELECT_TOOL_BIP85_INDEX]) {
        nbgl_layoutRelease(layout);
        nbgl_useCaseStatus("Under Construction\nComing soon", false, display_home_page);
    } else if (obj == screenChildren[SELECT_TOOL_BACK_BUTTON_INDEX]) {
        nbgl_layoutRelease(layout);
        display_home_page();
        return;
    }
}

static void display_select_tool_page(void) {
    nbgl_obj_t **screenChildren;

    // From top to bottom:
    // <return back arrow> + <icon> + <text> + <3 buttons>
    nbgl_screenSet(&screenChildren,
                   SELECT_TOOL_NB_CHILDREN,
                   NULL,
                   (nbgl_touchCallback_t) &select_tool_callback);

    screenChildren[SELECT_TOOL_ICON_INDEX] =
        (nbgl_obj_t *) generic_screen_set_icon(&C_seed_stax_64px);
    screenChildren[SELECT_TOOL_TEXT_INDEX] =
        (nbgl_obj_t *) generic_screen_set_title(screenChildren[SELECT_TOOL_ICON_INDEX]);
    ((nbgl_text_area_t *) screenChildren[SELECT_TOOL_TEXT_INDEX])->text =
        "\n\nSelect the tool\nyou wish to use";
    // create nb words buttons
    nbgl_objPoolGetArray(BUTTON,
                         SELECT_TOOL_NB_BUTTONS,
                         0,
                         (nbgl_obj_t **) &screenChildren[SELECT_TOOL_BIP39_INDEX]);
    generic_screen_configure_buttons((nbgl_button_t **) &screenChildren[SELECT_TOOL_BIP39_INDEX],
                                     SELECT_TOOL_NB_BUTTONS);
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_BIP39_INDEX])->text = toolType[0];
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_BIP39_INDEX])->icon = &C_bip39_stax_32px;
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_SSKR_INDEX])->text = toolType[1];
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_SSKR_INDEX])->icon = &C_sskr_stax_32px;
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_SSKR_INDEX])->borderColor = BLACK;
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_SSKR_INDEX])->innerColor = BLACK;
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_SSKR_INDEX])->foregroundColor = WHITE;
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_BIP85_INDEX])->text = toolType[2];
    ((nbgl_button_t *) screenChildren[SELECT_TOOL_BIP85_INDEX])->icon = &C_bip85_stax_32px;

    // create back button
    screenChildren[SELECT_TOOL_BACK_BUTTON_INDEX] = (nbgl_obj_t *) generic_screen_set_back_button();

    nbgl_screenRedraw();
}

/*
 * Select Recover BIP39
 */
static void select_recover_bip39_choice(bool bip39_rec) {
    if (bip39_rec) {
        nbgl_layoutRelease(layout);
        display_bip39_mnemonic();
    } else {
        nbgl_layoutRelease(layout);
        display_home_page();
    }
}

void display_select_recover_bip39_page(void) {
    nbgl_useCaseChoice(
        &C_bip39_stax_64px,
        "Recover BIP39 Phrase?",
        "Choose if you wish to\nrecover the BIP39 phrase\nfrom your valid\nSSKR shares.",
        "Recover BIP39",
        "Done",
        select_recover_bip39_choice);
}

/*
 * Select Generate SSKR
 */
static void select_generate_sskr_choice(bool sskr_gen) {
    if (sskr_gen) {
        nbgl_layoutRelease(layout);
        display_sskr_select_numshares_page();
    } else {
        nbgl_layoutRelease(layout);
        display_home_page();
    }
}

void display_select_generate_sskr_page(void) {
    nbgl_useCaseChoice(&C_sskr_stax_64px,
                       "Generate SSKR Phrase?",
                       "Choose if you wish to\ngenerate SSKR shares from\nyour valid BIP39 phrase.",
                       "Generate SSKR",
                       "Done",
                       select_generate_sskr_choice);
}

/*
 * Select mnemonic size page
 */
enum select_bip39_phrase_length {
    SELECT_BIP39_PHRASE_LENGTH_ICON_INDEX = 0,
    SELECT_BIP39_PHRASE_LENGTH_TEXT_INDEX,
    SELECT_BIP39_PHRASE_LENGTH_BUTTON_12_INDEX,
    SELECT_BIP39_PHRASE_LENGTH_BUTTON_18_INDEX,
    SELECT_BIP39_PHRASE_LENGTH_BUTTON_24_INDEX,
    SELECT_BIP39_PHRASE_LENGTH_BACK_BUTTON_INDEX,
    SELECT_BIP39_PHRASE_LENGTH_NB_CHILDREN,
    KBD_TEXT_TOKEN
};

#define SELECT_BIP39_PHRASE_LENGTH_NB_BUTTONS 3

static const char *bip39_passphraseLength[] = {"12 words", "18 words", "24 words"};
static void select_bip39_phrase_length_callback(nbgl_obj_t *obj, nbgl_touchType_t eventType) {
    nbgl_obj_t **screenChildren = nbgl_screenGetElements(0);
    if (eventType != TOUCHED) {
        return;
    }
    io_seproxyhal_play_tune(TUNE_TAP_CASUAL);
    if (obj == screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_12_INDEX]) {
        bip39_mnemonic_final_size_set(BIP39_MNEMONIC_SIZE_12);
    } else if (obj == screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_18_INDEX]) {
        bip39_mnemonic_final_size_set(BIP39_MNEMONIC_SIZE_18);
    } else if (obj == screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_24_INDEX]) {
        bip39_mnemonic_final_size_set(BIP39_MNEMONIC_SIZE_24);
    } else if (obj == screenChildren[SELECT_BIP39_PHRASE_LENGTH_BACK_BUTTON_INDEX]) {
        nbgl_layoutRelease(layout);
        display_select_tool_page();
        return;
    }
    nbgl_layoutRelease(layout);
    display_check_keyboard_page();
}

static void display_bip39_select_phrase_length_page(void) {
    nbgl_obj_t **screenChildren;

    // From top to bottom:
    // <return back arrow> + <icon> + <text> + <3 buttons>
    nbgl_screenSet(&screenChildren,
                   SELECT_BIP39_PHRASE_LENGTH_NB_CHILDREN,
                   NULL,
                   (nbgl_touchCallback_t) &select_bip39_phrase_length_callback);

    screenChildren[SELECT_BIP39_PHRASE_LENGTH_ICON_INDEX] =
        (nbgl_obj_t *) generic_screen_set_icon(&C_bip39_stax_64px);
    screenChildren[SELECT_BIP39_PHRASE_LENGTH_TEXT_INDEX] = (nbgl_obj_t *) generic_screen_set_title(
        screenChildren[SELECT_BIP39_PHRASE_LENGTH_ICON_INDEX]);
    ((nbgl_text_area_t *) screenChildren[SELECT_BIP39_PHRASE_LENGTH_TEXT_INDEX])->text =
        "\nHow long is your\nBIP39 Recovery\nPhrase?";

    // create nb words buttons
    nbgl_objPoolGetArray(
        BUTTON,
        SELECT_BIP39_PHRASE_LENGTH_NB_BUTTONS,
        0,
        (nbgl_obj_t **) &screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_12_INDEX]);
    generic_screen_configure_buttons(
        (nbgl_button_t **) &screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_12_INDEX],
        SELECT_BIP39_PHRASE_LENGTH_NB_BUTTONS);
    ((nbgl_button_t *) screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_12_INDEX])->text =
        bip39_passphraseLength[0];
    ((nbgl_button_t *) screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_18_INDEX])->text =
        bip39_passphraseLength[1];
    ((nbgl_button_t *) screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_24_INDEX])->text =
        bip39_passphraseLength[2];
    ((nbgl_button_t *) screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_24_INDEX])->borderColor =
        BLACK;
    ((nbgl_button_t *) screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_24_INDEX])->innerColor =
        BLACK;
    ((nbgl_button_t *) screenChildren[SELECT_BIP39_PHRASE_LENGTH_BUTTON_24_INDEX])
        ->foregroundColor = WHITE;

    // create back button
    screenChildren[SELECT_BIP39_PHRASE_LENGTH_BACK_BUTTON_INDEX] =
        (nbgl_obj_t *) generic_screen_set_back_button();

    nbgl_screenRedraw();
}

/*
 * Word recover page
 */
#define BUTTON_VMARGIN 32

enum check {
    CHECK_BACK_BUTTON_TOKEN = FIRST_USER_TOKEN,
    CHECK_FIRST_SUGGESTION_TOKEN,
    CHECK_RESULT_TOKEN,
};

static char textToEnter[BIP39_MAX_WORD_LENGTH + 1] = {0};
static int keyboardIndex = 0;
// the biggest word of BIP39 list is 8 char (9 with trailing '\0'), and
// the max number of showed suggestions is NB_MAX_SUGGESTION_BUTTONS
static char wordCandidates[(BIP39_MAX_WORD_LENGTH + 1) * NB_MAX_SUGGESTION_BUTTONS] = {0};

/*
 * Function called when a key of keyboard is touched
 */
static void key_press_callback(const char touchedKey) {
    size_t textLen = 0;
    uint32_t mask = 0;
    // Update word currently displayed
    const size_t previousTextLen = strlen(textToEnter);
    if (touchedKey == BACKSPACE_KEY) {
        if (previousTextLen == 0) {
            return;
        }
        textToEnter[previousTextLen - 1] = '\0';
        textLen = previousTextLen - 1;
    } else {
        textToEnter[previousTextLen] = touchedKey;
        textToEnter[previousTextLen + 1] = '\0';
        textLen = previousTextLen + 1;
    }

    // Update the screen (written word, suggestions, ...)
    nbgl_layoutSuggestionButtons_t suggestionButtons = {
        .buttons = PIC(buttonTexts),
        .firstButtonToken = CHECK_FIRST_SUGGESTION_TOKEN,
        .nbUsedButtons = 0,
    };
    nbgl_layoutKeyboardContent_t keyboardContent = {
        .type = KEYBOARD_WITH_SUGGESTIONS,
        .title = PIC(headerText),
        .text = PIC(textToEnter),
        .numbered = true,
        .number = onboarding_type == ONBOARDING_TYPE_BIP39
                      ? bip39_mnemonic_current_word_number_get() + 1
                      : sskr_shares_current_word_number_get() + 1,
        .grayedOut = false,
        .textToken = KBD_TEXT_TOKEN,
        .suggestionButtons = suggestionButtons,
        .tuneId = TUNE_TAP_CASUAL,
    };
    PRINTF("Current text is: '%s' (size '%d')\n", textToEnter, textLen);

    if (textLen < 2) {
        // Suggestions only when the word contains 2+ letters
        nbgl_layoutUpdateKeyboardContent(layout, &keyboardContent);
    } else {
        const size_t nbMatchingWords =
            onboarding_type == ONBOARDING_TYPE_BIP39
                ? bolos_ux_bip39_fill_with_candidates((unsigned char *) &(textToEnter[0]),
                                                      strlen(textToEnter),
                                                      wordCandidates,
                                                      buttonTexts)
                : bolos_ux_sskr_fill_with_candidates((unsigned char *) &(textToEnter[0]),
                                                     strlen(textToEnter),
                                                     wordCandidates,
                                                     buttonTexts);
        keyboardContent.suggestionButtons.nbUsedButtons = nbMatchingWords;
        nbgl_layoutUpdateKeyboardContent(layout, &keyboardContent);
    }
    if (textLen > 0) {
        mask = onboarding_type == ONBOARDING_TYPE_BIP39
                   ? bolos_ux_bip39_get_keyboard_mask((unsigned char *) &(textToEnter[0]),
                                                      strlen(textToEnter))
                   : bolos_ux_sskr_get_keyboard_mask((unsigned char *) &(textToEnter[0]),
                                                     strlen(textToEnter));
    }
    nbgl_layoutDraw(layout);
    nbgl_layoutUpdateKeyboard(layout, keyboardIndex, mask, false, LOWER_CASE);
    nbgl_refreshSpecialWithPostRefresh(BLACK_AND_WHITE_REFRESH, POST_REFRESH_FORCE_POWER_ON);
}

static void bip39_keyboard_dispatcher(const int token, uint8_t index) {
    UNUSED(index);
    if (token == CHECK_BACK_BUTTON_TOKEN) {
        nbgl_layoutRelease(layout);
        if (bip39_mnemonic_word_remove()) {
            display_check_keyboard_page();
        } else {
            bip39_mnemonic_reset();
            display_bip39_select_phrase_length_page();
        }
    } else if (token >= CHECK_FIRST_SUGGESTION_TOKEN) {
        nbgl_layoutRelease(layout);
        PRINTF("Selected word is '%s' (size '%d')\n",
               buttonTexts[token - CHECK_FIRST_SUGGESTION_TOKEN],
               strlen(buttonTexts[token - CHECK_FIRST_SUGGESTION_TOKEN]));
        bip39_mnemonic_word_add(buttonTexts[token - CHECK_FIRST_SUGGESTION_TOKEN],
                                strlen(buttonTexts[token - CHECK_FIRST_SUGGESTION_TOKEN]));
        if (bip39_mnemonic_complete_check()) {
            display_check_result_page(bip39_mnemonic_check());
        } else {
            display_check_keyboard_page();
        }
    }
}

static void sskr_keyboard_dispatcher(const int token, uint8_t index) {
    UNUSED(index);
    if (token == CHECK_BACK_BUTTON_TOKEN) {
        nbgl_layoutRelease(layout);
        if (sskr_shares_word_remove()) {
            display_check_keyboard_page();
        } else {
            sskr_shares_reset();
            display_select_tool_page();
        }
    } else if (token >= CHECK_FIRST_SUGGESTION_TOKEN) {
        nbgl_layoutRelease(layout);
        PRINTF("Selected word is '%s' (size '%d')\n",
               buttonTexts[token - CHECK_FIRST_SUGGESTION_TOKEN],
               strlen(buttonTexts[token - CHECK_FIRST_SUGGESTION_TOKEN]));
        sskr_shares_word_add(buttonTexts[token - CHECK_FIRST_SUGGESTION_TOKEN]);
        if (sskr_shares_complete_check()) {
            display_check_result_page(sskr_shares_check());
        } else {
            display_check_keyboard_page();
        }
    }
}

static void display_check_keyboard_page() {
    nbgl_layoutDescription_t layoutDescription = {
        .modal = false,
        .onActionCallback = onboarding_type == ONBOARDING_TYPE_BIP39 ? &bip39_keyboard_dispatcher
                                                                     : &sskr_keyboard_dispatcher};
    nbgl_layoutKbd_t kbdInfo = {.lettersOnly = true,   // use only letters
                                .mode = MODE_LETTERS,  // start in letters mode
                                .keyMask = 0,          // no inactive key
                                .callback = &key_press_callback};
    textToEnter[0] = '\0';
    memzero(buttonTexts, sizeof(buttonTexts[0]) * NB_MAX_SUGGESTION_BUTTONS);
    layout = nbgl_layoutGet(&layoutDescription);
    if (onboarding_type == ONBOARDING_TYPE_BIP39) {
        snprintf(headerText,
                 HEADER_SIZE,
                 "Enter word n. %d/%d of your\nBIP39 Recovery Phrase",
                 bip39_mnemonic_current_word_number_get() + 1,
                 bip39_mnemonic_final_size_get());
    } else if (onboarding_type == ONBOARDING_TYPE_SSKR) {
        snprintf(headerText,
                 HEADER_SIZE,
                 "Enter Share %d Word %d\nof your Recovery Phrase",
                 sskr_shareindex_get() + 1,
                 sskr_shares_current_word_number_get() + 1);
    }

    nbgl_layoutHeader_t headerDesc = {.type = HEADER_BACK_AND_TEXT,
                                      .separationLine = false,
                                      .backAndText.token = CHECK_BACK_BUTTON_TOKEN,
                                      .backAndText.tuneId = TUNE_TAP_CASUAL,
                                      .backAndText.text = NULL};
    nbgl_layoutAddHeader(layout, &headerDesc);

    keyboardIndex = nbgl_layoutAddKeyboard(layout, &kbdInfo);

    nbgl_layoutSuggestionButtons_t suggestionButtons = {
        .buttons = PIC(buttonTexts),
        .firstButtonToken = CHECK_FIRST_SUGGESTION_TOKEN,
        .nbUsedButtons = 0,
    };
    nbgl_layoutKeyboardContent_t keyboardContent = {
        .type = KEYBOARD_WITH_SUGGESTIONS,
        .title = PIC(headerText),
        .text = PIC(textToEnter),
        .numbered = true,
        .number = onboarding_type == ONBOARDING_TYPE_BIP39
                      ? bip39_mnemonic_current_word_number_get() + 1
                      : sskr_shares_current_word_number_get() + 1,
        .grayedOut = false,
        .textToken = KBD_TEXT_TOKEN,
        .suggestionButtons = suggestionButtons,
        .tuneId = TUNE_TAP_CASUAL,
    };
    nbgl_layoutAddKeyboardContent(layout, &keyboardContent);
    nbgl_layoutDraw(layout);
}

/*
 * Home page, infos & dispatcher
 */
static void display_home_page() {
    static const char *const infoTypes[] = {"Version", APPNAME};
    static const char *const infoContents[] = {APPVERSION, "(c) 2018-2024 Ledger"};
    static const nbgl_contentInfoList_t infoList = {.nbInfos = 2,
                                                    .infoTypes = infoTypes,
                                                    .infoContents = infoContents};

    reset_globals();

    nbgl_homeAction_t action = {.text = "Select Tool", .callback = PIC(display_select_tool_page)};

    nbgl_useCaseHomeAndSettings(
        APPNAME,
        &C_seed_stax_64px,
        "This Ledger application\nprovides some useful seed\nmanagement utilities.",
        INIT_HOME_PAGE,
        NULL,
        &infoList,
        &action,
        on_quit);
}

#if defined(TARGET_STAX)
#define DEVICE "Ledger Stax"
#elif defined(TARGET_FLEX)
#define DEVICE "Ledger Flex"
#endif

/*
 * Result page
 */
static void check_result_callback(int token __attribute__((unused)),
                                  uint8_t index __attribute__((unused))) {
    if (onboarding_type == ONBOARDING_TYPE_BIP39 && bip39_mnemonic_check()) {
        display_select_generate_sskr_page();
    } else if (onboarding_type == ONBOARDING_TYPE_SSKR && sskr_shares_check()) {
        display_select_recover_bip39_page();
    } else {
        reset_globals();
        display_home_page();
    }
}

static void display_check_result_page(const bool result) {
    static const char *possible_results[2][3] = {
        {"Incorrect Secret\nRecovery Phrase",
         "The BIP39 Recovery Phrase\nyou have entered\ndoesn't match the one present\n"
         "on this " DEVICE ".",
         "The SSKR Recovery Phrase\nyou have entered is not valid"},
        {"Correct Secret\nRecovery Phrase",
         "The BIP39 Recovery Phrase\nyou have entered\nmatches the one present\n"
         "on this " DEVICE ".",
         "The SSKR Recovery Phrase\nyou have entered is valid"}};
    static const nbgl_icon_details_t *icons[2] = {&C_Warning_64px, &C_Check_Circle_64px};

    nbgl_pageInfoDescription_t info = {
        .centeredInfo.icon = icons[result],
        .centeredInfo.text1 = possible_results[result][0],
        .centeredInfo.text2 = possible_results[result][1 + onboarding_type],
        .centeredInfo.text3 = NULL,
        .centeredInfo.style = LARGE_CASE_INFO,
        .centeredInfo.offsetY = -16,
        .footerText = "Tap to dismiss",
        .footerToken = CHECK_RESULT_TOKEN,
        .bottomButtonStyle = NO_BUTTON_STYLE,
        .tapActionText = NULL,
        .topRightStyle = NO_BUTTON_STYLE,
        .actionButtonText = NULL,
        .tuneId = TUNE_TAP_CASUAL};
    pageContext = nbgl_pageDrawInfo(&check_result_callback, NULL, &info);
    nbgl_refresh();
}

/*
 * Select number of shares page
 */

enum sskr_gen {
    SSKR_GEN_BACK_BUTTON_TOKEN = FIRST_USER_TOKEN,
    SSKR_GEN_SELECT_SHARENUM_TOKEN,
    SSKR_GEN_SELECT_THRESHOLD_TOKEN,
    SSKR_GEN_RESULT_TOKEN,
};

static void sskr_sharenum_validate(const uint8_t *sharenumentry, uint8_t length) {
    // Code to validate the entered shares number

    sskr_sharenum_set(0);

    for (uint8_t i = 0; i < length; i++) {
        sskr_sharenum_set(10 * sskr_sharenum_get() + sharenumentry[i] - '0');
    }

    PRINTF("Number of shares entered is '%d'\n", sskr_sharenum_get());

    if (sskr_sharenum_get() > 0 && sskr_sharenum_get() <= 16) {
        display_sskr_select_threshold_page();
    } else {
        nbgl_useCaseStatus("Number of SSKR shares must be between 1 and 16",
                           false,
                           display_select_generate_sskr_page);
    }
}

static void sskr_sharenum_entry_cb(int token, uint8_t index) {
    UNUSED(index);
    // Callback for the key navigation (back key mainly)
    if (token == SSKR_GEN_BACK_BUTTON_TOKEN) {
        display_select_generate_sskr_page();
    }
}

void display_sskr_select_numshares_page() {
    // Draw the keypad
    nbgl_useCaseKeypadDigits("Enter number of SSKR shares\nto generate (1 - 16)",
                             1,
                             MAX_NUMBER_LENGTH,
                             SSKR_GEN_BACK_BUTTON_TOKEN,
                             false,
                             TUNE_TAP_CASUAL,
                             sskr_sharenum_validate,
                             sskr_sharenum_entry_cb);
}

char item_buffer[15];
char value_buffer[(SSKR_SHARES_MAX_LENGTH / 16) + 1];

static void review_done(void) {
    memzero(item_buffer, sizeof(item_buffer));
    memzero(value_buffer, sizeof(value_buffer));
    reset_globals();

    display_home_page();
}

static void display_bip39_mnemonic(void) {
    bip39_mnemonic_from_sskr_shares();

    static nbgl_layoutTagValue_t pairs[1];
    static const nbgl_content_t content[1] = {
        {.type = TAG_VALUE_LIST,
         .contentActionCallback = NULL,
         .content.tagValueList.nbPairs = 1,
         .content.tagValueList.nbMaxLinesForValue = 0,
         .content.tagValueList.wrapping = true,
         .content.tagValueList.pairs = (nbgl_layoutTagValue_t *) pairs}};
    static const nbgl_genericContents_t genericContent = {.callbackCallNeeded = false,
                                                          .contentsList = content,
                                                          .nbContents = 1};

    SPRINTF(item_buffer, "BIP39 Phrase");
    pairs[0].item = item_buffer;

    strncpy(value_buffer, bip39_mnemonic_get(), bip39_mnemonic_length_get());
    // Ensure null termination
    value_buffer[bip39_mnemonic_length_get()] = '\0';
    pairs[0].value = value_buffer;

    nbgl_useCaseGenericReview(&genericContent, "Done", review_done);
}

static void review_sskr_shares_contentGetter(uint8_t index, nbgl_content_t *genericreview) {
    static nbgl_layoutTagValue_t pairs[1];

    genericreview->type = TAG_VALUE_LIST;
    genericreview->contentActionCallback = NULL;
    genericreview->content.tagValueList.nbPairs = 1;
    genericreview->content.tagValueList.nbMaxLinesForValue = 0;
    genericreview->content.tagValueList.wrapping = true;
    genericreview->content.tagValueList.pairs = (nbgl_layoutTagValue_t *) pairs;

    SPRINTF(item_buffer, "SSKR Share #%d", index + 1);
    // Ensure null termination
    item_buffer[sskr_sharecount_get() > 9 ? sizeof(item_buffer) - 1 : sizeof(item_buffer) - 2] =
        '\0';
    pairs[0].item = item_buffer;

    strncpy(value_buffer,
            sskr_shares_get() + (index * sskr_shares_length_get() / sskr_sharecount_get()),
            sskr_shares_length_get() / sskr_sharecount_get());
    // Ensure null termination
    value_buffer[sskr_shares_length_get() / sskr_sharecount_get()] = '\0';
    pairs[0].value = value_buffer;
}

static void display_sskr_shares(void) {
    sskr_shares_from_bip39_mnemonic();

    static nbgl_genericContents_t genericContent;
    genericContent.callbackCallNeeded = true;
    genericContent.contentGetterCallback = review_sskr_shares_contentGetter;
    genericContent.nbContents = sskr_sharecount_get();

    nbgl_useCaseGenericReview(&genericContent, "Done", review_done);
}

static void sskr_threshold_validate(const uint8_t *thresholdentry, uint8_t length) {
    // Code to validate the entered threshold number

    sskr_threshold_set(0);

    for (uint8_t i = 0; i < length; i++) {
        sskr_threshold_set(10 * sskr_threshold_get() + thresholdentry[i] - '0');
    }

    PRINTF("Threshold value entered is '%d'\n", sskr_sharenum_get());

    if (sskr_threshold_get() < 1) {
        nbgl_useCaseStatus("Threshold value cannot be 0", false, display_select_generate_sskr_page);
    } else if (sskr_threshold_get() > sskr_sharenum_get()) {
        nbgl_useCaseStatus("Threshold value cannot be greater than number of shares",
                           false,
                           display_select_generate_sskr_page);
    } else if (sskr_sharenum_get() == 1 && sskr_sharenum_get() > 1) {
        nbgl_useCaseStatus("1-of-m shares where m > 1 is not supported",
                           false,
                           display_select_generate_sskr_page);
    } else {
        display_sskr_shares();
    }
}

static void sskr_threshold_entry_cb(int token, uint8_t index) {
    UNUSED(index);
    // Callback for the key navigation (back key mainly)
    if (token == SSKR_GEN_BACK_BUTTON_TOKEN) {
        display_sskr_select_numshares_page();
    }
}

void display_sskr_select_threshold_page() {
    // Draw the keypad
    nbgl_useCaseKeypadDigits("Enter threshold value",
                             1,
                             MAX_NUMBER_LENGTH,
                             SSKR_GEN_BACK_BUTTON_TOKEN,
                             false,
                             TUNE_TAP_CASUAL,
                             sskr_threshold_validate,
                             sskr_threshold_entry_cb);
}

/*
 * Public function
 */
void ui_idle_init(void) {
    display_home_page();
}
#endif
