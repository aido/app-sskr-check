#include <os.h>
#include <string.h>

#include "../common/common.h"
#include "../common/bip39/common_bip39.h"
#include "../common/sskr/common_sskr.h"
#include "./bip39_mnemonic.h"
#include "./sskr_shares.h"

#if defined(SCREEN_SIZE_WALLET)

typedef struct bip39_buffer_struct {
    // the mnemonic passphrase, built over time
    char buffer[BIP39_MNEMONIC_MAX_LENGTH];
    // current length of the mnemonic passphrase
    size_t length;
    // index of the current word ((size_t)-1 mean there is no word currently)
    size_t current_word_index;
    // array of every stored word lengths (used for removing them if needed)
    size_t word_lengths[BIP39_MNEMONIC_SIZE_24];
    // expected number of word in the final mnemonic (12 or 18 or 24)
    size_t final_size;
} bip39_buffer_t;

static bip39_buffer_t mnemonic = {0};

size_t bip39_mnemonic_shrink(const size_t size) {
    if (size == 0 || size > mnemonic.length) {
        // shrink all
        mnemonic.length = 0;
    } else {
        mnemonic.length -= size;
    }
    memzero(&mnemonic.buffer[mnemonic.length], BIP39_MNEMONIC_MAX_LENGTH - mnemonic.length);
    return mnemonic.length;
}

void bip39_mnemonic_final_size_set(const size_t size) {
    mnemonic.final_size = size;
}

size_t bip39_mnemonic_final_size_get(void) {
    return mnemonic.final_size;
}

size_t bip39_mnemonic_current_word_number_get(void) {
    return mnemonic.current_word_index + 1;
}

void bip39_mnemonic_reset(void) {
    memzero(&mnemonic, sizeof(mnemonic));
    mnemonic.current_word_index = (size_t) -1;
}

bool bip39_mnemonic_word_remove(void) {
    PRINTF("Removing a word, currently there is '%d' of them\n", mnemonic.current_word_index + 1);
    if (mnemonic.current_word_index == (size_t) -1) {
        return false;
    }
    const size_t current_length = mnemonic.word_lengths[mnemonic.current_word_index];
    mnemonic.current_word_index--;
    // removing previous word from mnemonic buffer (+ 1 blank space)
    bip39_mnemonic_shrink(current_length + 1);
    PRINTF("Number of remaining words in the mnemonic: '%d'\n", mnemonic.current_word_index + 1);
    return true;
}

size_t bip39_mnemonic_word_add(const char* const buffer, const size_t size) {
    if (mnemonic.current_word_index != (size_t) -1) {
        // adding an extra white space ' ' between words
        mnemonic.buffer[mnemonic.length++] = ' ';
        mnemonic.buffer[mnemonic.length] = '\0';
    }
    memcpy(&mnemonic.buffer[0] + mnemonic.length, buffer, size);
    mnemonic.length += size;
    mnemonic.current_word_index++;
    mnemonic.word_lengths[mnemonic.current_word_index] = size;
    PRINTF("Number of words in the mnemonic: '%d'\n", bip39_mnemonic_current_word_number_get());
    PRINTF("Current mnemonic: '%s'\n", &mnemonic.buffer[0]);
    return bip39_mnemonic_current_word_number_get();
}

bool bip39_mnemonic_complete_check(void) {
    return (mnemonic.final_size == 0
                ? false
                : (mnemonic.current_word_index + 1) >= bip39_mnemonic_final_size_get());
}

bool bip39_mnemonic_check(bool* match) {
    *match = false;
    if (!bip39_mnemonic_complete_check()) {
        return false;
    }
    PRINTF("Checking the following mnemonic: '%s' (size %d)\n",
           &mnemonic.buffer[0],
           mnemonic.length);

    if (bolos_ux_bip39_mnemonic_check((unsigned char*) &mnemonic.buffer[0], mnemonic.length) ==
        false) {
        bip39_mnemonic_reset();
        return false;
    }

    *match = compare_recovery_phrase();
    // Don't clear the mnemonic just yet as we may need it to generate SSKR shares
    //    bip39_mnemonic_reset();

    return true;
}

void bip39_mnemonic_from_sskr_shares(unsigned char* seed) {
    mnemonic.length = BIP39_MNEMONIC_MAX_LENGTH;

    bolos_ux_sskr_to_seed_convert((const unsigned char*) sskr_shares_get(),
                                  sskr_shares_length_get(),
                                  sskr_sharecount_get(),
                                  (const unsigned char*) bip39_mnemonic_get(),
                                  &mnemonic.length,
                                  seed);

    if (mnemonic.length > 0) {
        PRINTF("BIP39 mnemonic: %.*s\n", mnemonic.length, bip39_mnemonic_get());
    }
}

// Used for BIP39 <-> SSKR roundtrip
char* bip39_mnemonic_get(void) {
    return mnemonic.buffer;
}

size_t bip39_mnemonic_length_get(void) {
    return mnemonic.length;
}

#endif
