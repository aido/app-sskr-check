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

#include <os.h>
#include <cx.h>
#include <ux.h>
#include <os_io_seproxyhal.h>

#include "ui.h"

#if defined(HAVE_BAGL)
extern enum UI_STATE uiState;
#endif

static unsigned int current_text_pos;  // parsing cursor in the text to display
static unsigned int text_y;            // current location of the displayed text

// UI currently displayed
enum UI_STATE { UI_IDLE, UI_TEXT, UI_APPROVAL };

void app_main(void) {
    current_text_pos = 0;
    text_y = 60;
#if defined(HAVE_BAGL)
    uiState = UI_IDLE;
#endif

#if defined(HAVE_NBGL)
    nbgl_objInit();
#elif defined(HAVE_BAGL)
    UX_INIT();
#endif

    ui_idle_init();

    uint8_t flags = 0;

    for (;;) {
        io_exchange(CHANNEL_APDU | flags, 0);

        flags |= IO_ASYNCH_REPLY;
    }
    return;
}

unsigned char io_event(unsigned char channel __attribute__((unused))) {
    // nothing done with the event, throw an error on the transport layer if
    // needed

    // can't have more than one tag in the reply, not supported yet.
    switch (G_io_seproxyhal_spi_buffer[0]) {
        case SEPROXYHAL_TAG_FINGER_EVENT:
            UX_FINGER_EVENT(G_io_seproxyhal_spi_buffer);
            break;
#if !defined(HAVE_NBGL)
        case SEPROXYHAL_TAG_BUTTON_PUSH_EVENT:  // for Nano S
            UX_BUTTON_PUSH_EVENT(G_io_seproxyhal_spi_buffer);
            break;
#endif
        case SEPROXYHAL_TAG_DISPLAY_PROCESSED_EVENT:
#if defined(TARGET_NANOS)
            if ((uiState == UI_TEXT) &&
                (os_seph_features() & SEPROXYHAL_TAG_SESSION_START_EVENT_FEATURE_SCREEN_BIG)) {
                UX_REDISPLAY();
            } else {
                if (G_bolos_ux_context.processing == PROCESSING_COMPARE_RECOVERY_PHRASE) {
                    UX_DISPLAYED_EVENT(compare_recovery_phrase(););
                } else if (G_bolos_ux_context.processing == PROCESSING_GENERATE_SSKR) {
                    UX_DISPLAYED_EVENT(generate_sskr(););
                } else {
                    UX_DISPLAYED_EVENT();
                }
            }
#elif defined(TARGET_NANOX) || defined(TARGET_NANOS2)
            UX_DISPLAYED_EVENT({});
#elif defined(HAVE_NBGL)
            UX_DEFAULT_EVENT();
#endif
            break;

        case SEPROXYHAL_TAG_TICKER_EVENT:
            UX_TICKER_EVENT(G_io_seproxyhal_spi_buffer, {
                // default retrig very soon (will be overridden during
                // stepper_prepro)
                UX_CALLBACK_SET_INTERVAL(500);
                UX_REDISPLAY();
            });
            break;

        // unknown events are acknowledged
        default:
            UX_DEFAULT_EVENT();
            break;
    }

    // close the event if not done previously (by a display or whatever)
    if (!io_seproxyhal_spi_is_status_sent()) {
        io_seproxyhal_general_status();
    }

    // command has been processed, DO NOT reset the current APDU transport
    return 1;
}
