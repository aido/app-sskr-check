#include <os.h>
#include <string.h>

#include "../ux_common/common_sskr.h"
#include "./sskr_shares.h"
#include "./bip39_mnemonic.h"

#if defined(TARGET_STAX)

typedef struct sskr_buffer_struct {
    // The SSKR shares, built over time
    char buffer[SSKR_SHARES_MAX_LENGTH];
    // current length of the shares buffer
    unsigned int length;
    unsigned int group_descriptor[1][2];
    uint8_t count;
} sskr_buffer_t;

static sskr_buffer_t shares = {0};

void sskr_sharenum_set(const uint8_t sharenum) {
    shares.group_descriptor[0][1] = sharenum;
}

uint8_t sskr_sharenum_get(void) {
    return shares.group_descriptor[0][1];
}

void sskr_threshold_set(const uint8_t threshold) {
    shares.group_descriptor[0][0] = threshold;
}

uint8_t sskr_threshold_get(void) {
    return shares.group_descriptor[0][0];
}

uint8_t sskr_sharecount_get(void) {
    return shares.count;
}

void sskr_shares_reset(void) {
    memzero(&shares, sizeof(shares));
}

void sskr_shares_from_bip39_mnemonic(void) {
    shares.length = 0;

    bolos_ux_bip39_to_sskr_convert((unsigned char*) bip39_mnemonic_get(),
                                   bip39_mnemonic_length_get(),
                                   bip39_mnemonic_final_size_get(),
                                   shares.group_descriptor[0],
                                   &shares.count,
                                   (unsigned char*) shares.buffer,
                                   &shares.length);

    if (shares.count > 0) {
        PRINTF("SSKR share count is %d\n", shares.count);
        PRINTF("SSKR share buffer length is %d\n", shares.length);
        for (uint8_t share = 0; share < shares.count; share++) {
            PRINTF("SSKR share %d:\n", share + 1);
            PRINTF("%.*s\n",
                   shares.length / shares.count,
                   shares.buffer + share * shares.length / shares.count);
        }
    }
}

char* sskr_shares_get(void) {
    return shares.buffer;
}

size_t sskr_shares_length_get(void) {
    return shares.length;
}
#endif
