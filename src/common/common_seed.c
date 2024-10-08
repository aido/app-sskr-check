/*******************************************************************************
 *   (c) 2016-2024 Ledger SAS
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

#include <lcx_hmac.h>

#include "constants.h"
#include "ui.h"
#include "./common.h"
#include "./bip39/common_bip39.h"
#if defined(HAVE_NBGL)
#include "../nbgl/bip39_mnemonic.h"
extern unsigned int onboarding_type;
#endif

bool compare_recovery_phrase(void) {
    // convert mnemonic to hex-seed
    uint8_t buffer[64];

#if defined(HAVE_BAGL)
    if (G_bolos_ux_context.onboarding_type == ONBOARDING_TYPE_BIP39) {
        bolos_ux_bip39_mnemonic_to_seed((unsigned char*) G_bolos_ux_context.words_buffer,
                                        G_bolos_ux_context.words_buffer_length,
                                        buffer);
    } else if (G_bolos_ux_context.onboarding_type == ONBOARDING_TYPE_SSKR) {
        G_bolos_ux_context.words_buffer_length = sizeof(G_bolos_ux_context.words_buffer);
        bolos_ux_sskr_to_seed_convert((unsigned char*) G_bolos_ux_context.sskr_words_buffer,
                                      G_bolos_ux_context.sskr_words_buffer_length,
                                      G_bolos_ux_context.sskr_share_count,
                                      (unsigned char*) &G_bolos_ux_context.words_buffer,
                                      &G_bolos_ux_context.words_buffer_length,
                                      buffer);
    }
#elif defined(HAVE_NBGL)
    if (onboarding_type == ONBOARDING_TYPE_BIP39) {
        bolos_ux_bip39_mnemonic_to_seed((const unsigned char *) bip39_mnemonic_get(),
                                        bip39_mnemonic_length_get(),
                                        buffer);
    } else if (onboarding_type == ONBOARDING_TYPE_SSKR) {
        bip39_mnemonic_from_sskr_shares(buffer);
    }
#endif
    PRINTF("Input seed:\n %.*H\n", 64, buffer);

    // get rootkey from hex-seed
    cx_hmac_sha512_t ctx;
    const char key[] = "Bitcoin seed";

    LEDGER_ASSERT(cx_hmac_sha512_init_no_throw(&ctx, (const uint8_t*) key, strlen(key)) == CX_OK,
                  "HMAC init failed");
    LEDGER_ASSERT(cx_hmac_no_throw((cx_hmac_t*) &ctx, CX_LAST, buffer, 64, buffer, 64) == CX_OK,
                  "HMAC failed");
    PRINTF("Root key from input:\n%.*H\n", 64, buffer);

    // get rootkey from device's seed
    uint8_t buffer_device[64];

    // os_derive_bip32* do not accept NULL path, even with a size of 0, so we provide an empty path
    const unsigned int empty_path = 0;
    if (os_derive_bip32_no_throw(CX_CURVE_256K1,
                                 &empty_path,
                                 0,
                                 buffer_device,
                                 buffer_device + 32) != CX_OK) {
        PRINTF("An error occurred while comparing the recovery phrase\n");
        return 0;
    }
    PRINTF("Root key from device: \n%.*H\n", 64, buffer_device);

    // compare both rootkey
    const bool result = os_secure_memcmp(buffer, buffer_device, 64) ? false : true;
    memzero(buffer_device, 64);
    memzero(buffer, 64);

    return result;
}
