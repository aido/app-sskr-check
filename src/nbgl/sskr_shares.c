#include <os.h>
#include <string.h>

#include "../common/sskr/common_sskr.h"
#include "./sskr_shares.h"
#include "./bip39_mnemonic.h"

#if defined(SCREEN_SIZE_WALLET)

typedef struct sskr_buffer_struct {
    // The SSKR shares, built over time
    char buffer[SSKR_SHARES_MAX_LENGTH];
    // current length of the shares buffer
    unsigned int length;
    // index of the current word ((size_t)-1 mean there is no word currently)
    size_t current_word_index;
    // index of the current share ((uint8_t)-1 mean there is no share currently)
    uint8_t current_share_index;
    unsigned int group_descriptor[1][2];
    uint8_t count;
    // expected number of words in the share
    size_t final_size;

} sskr_buffer_t;

static sskr_buffer_t shares = {0};

size_t sskr_shares_shrink(const size_t size) {
    if (size == 0 || size > shares.length) {
        // shrink all
        shares.length = 0;
    } else {
        shares.length -= size;
    }
    memzero(&shares.buffer[shares.length], SSKR_SHARES_MAX_LENGTH - shares.length);
    return shares.length;
}

bool sskr_shares_word_remove(void) {
    PRINTF("Removing a word, currently there is '%d' of them\n", shares.current_word_index + 1);
    if (shares.current_word_index == (size_t) -1) {
        return false;
    }
    shares.current_word_index--;
    // removing previous word from shares buffer (+ 1 blank space)
    sskr_shares_shrink(1);
    PRINTF("Number of remaining words in the shares: '%d'\n", shares.current_word_index + 1);
    return true;
}

size_t sskr_shares_current_word_number_get(void) {
    return shares.current_word_index + 1;
}

size_t sskr_shares_word_add(const char* const byteword) {
    shares.buffer[shares.length] = bolos_ux_sskr_byteword_to_hex((unsigned char*) byteword);
    switch (sskr_shares_current_word_number_get()) {
        // 4th byte of CBOR header contains number of data bytes to follow
        case 3:
            // SSKR bytes = 4 bytes CBOR + n bytes share + 4 bytes CRC checksum
            shares.final_size = 4 + (shares.buffer[shares.length] & 0x1F) + sizeof(uint32_t);
            break;
        case 4:
            if ((shares.buffer[3] & 0x1F) == 24) {
                shares.final_size = 4 + 1 + shares.buffer[shares.length] + sizeof(uint32_t);
            }
            PRINTF("SSKR final number of words in this share: %d\n", shares.final_size);
            break;
        // 8th byte of SSKR phrase contains member-threshold
        case 7:
            if ((shares.buffer[3] & 0x1F) < 24) {
                shares.count = (shares.buffer[shares.length] & 0x0F) + 1;
            }
            break;
        case 8:
            if ((shares.buffer[3] & 0x1F) == 24) {
                shares.count = (shares.buffer[shares.length] & 0x0F) + 1;
            }
            break;
    }
    shares.length++;
    shares.current_word_index++;

    PRINTF("Current number of words in the share: '%d'\n", sskr_shares_current_word_number_get());
    PRINTF("Current shares buffer: '%.*H'\n", shares.length, &shares.buffer[0]);

    return sskr_shares_current_word_number_get();
}

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

uint8_t sskr_shareindex_get(void) {
    return shares.current_share_index + 1;
}

void sskr_shares_reset(void) {
    memzero(&shares, sizeof(shares));
    shares.current_word_index = (size_t) -1;
    shares.current_share_index = (uint8_t) -1;
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

bool sskr_shares_complete_check(void) {
    // We won't know final size until after word 5
    if (sskr_shares_current_word_number_get() < 5 ||
        sskr_shares_current_word_number_get() < shares.final_size) {
        return false;
    }

    shares.current_share_index++;

    if (sskr_shareindex_get() < sskr_sharecount_get()) {
        shares.current_word_index = (size_t) -1;
        return false;
    }

    return true;
}

bool sskr_shares_check(void) {
    if (!sskr_shares_complete_check()) {
        return false;
    }

    PRINTF("Checking the following shares: '%.*H' (size %d)\n",
           shares.length,
           &shares.buffer[0],
           shares.length);

    const bool result = bolos_ux_sskr_hex_check((unsigned char*) sskr_shares_get(),
                                                sskr_shares_length_get(),
                                                sskr_sharecount_get());

    // Don't clear the shares just yet as we may need it to generate BIP39 mnemonic
    // sskr_shares_reset();

    return result;
}

char* sskr_shares_get(void) {
    return shares.buffer;
}

size_t sskr_shares_length_get(void) {
    return shares.length;
}
#endif
