/*
* The test seeds and shares used for these tests have been taken from:
*     https://github.com/BlockchainCommons/crypto-commons/blob/master/Docs/sskr-test-vector.md#256-bit-seed
*
* The seed is generated from the following BIP39 words:
*     toe priority custom gauge jacket theme arrest bargain
*     gloom wide ill fit eagle prepare capable fish limb
*     cigar reform other priority speak rough imitate
* 
* The set of 2-of-3 shares as SSKR ByteWords are:
*     tuna acid epic hard data love wolf able acid able
*     duty surf belt task judo legs ruby cost belt pose
*     ruby logo iron vows luck bald user lazy tuna belt
*     guru buzz limp exam obey kept task cash saga pool
*     love brag roof owls news junk
* 
*     tuna acid epic hard data love wolf able acid acid
*     barn peck luau keys each duty waxy quad open bias
*     what cusp zaps math kick dark join nail legs oboe
*     also twin yank road very blue gray saga oboe city
*     gear beta quad draw knob main
* 
*     tuna acid epic hard data love wolf able acid also
*     fund able city road whiz zone claw high frog work
*     deli slot gush cats kiwi gyro numb puma join fund
*     when math inch even curl rich vows oval also unit
*     brew door atom love gyro figs
*
* SSKR is non-deterministic. There is a random factor introduced when the shares are created, which means
* that every time you generate shares, they will be different. This is an expected and correct result.
*
* However, these tests use a fake random number generator so the shares generated by the tests will
* be predictable. The shares generated by these tests will consistently be: 
*
*     tuna acid epic hard data acid able able acid able
*     zoom bias rock door luau surf jowl able soap visa
*     legs user puff warm hope code gyro webs brag tuna
*     gear iced miss flew flew twin curl body road skew
*     hope peck peck echo able tiny
*
*     tuna acid epic hard data acid able able acid acid
*     quiz main lazy note rock love code scar task zero
*     blue rock slot real mint roof ruby quad glow cook
*     curl taco aqua meow fund cook kick luck belt knob
*     wand oboe lava urge help exit
*
*     tuna acid epic hard data acid able able acid also
*     iron calm task help warm fizz loud next skew undo
*     ruin cash holy guru tomb fuel noon hang paid gems
*     note curl peck yank half gala maze duty task poem
*     drum road film brew flew trip
*/

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include "testutils.h"
#include "constants.h"
#include "common_bip39.h"
#include "common_sskr.h"

const unsigned char bip39_mnemonic[] = "toe priority custom gauge jacket theme arrest bargain gloom wide ill fit eagle prepare capable fish limb cigar reform other priority speak rough imitate";

const uint8_t bip39_hex[] = {0xE3, 0x95, 0x5C, 0xDA, 0x30, 0x47, 0x71, 0xC0,
                             0x03, 0x18, 0x95, 0x63, 0x7F, 0x55, 0xC3, 0xAB,
                             0xE4, 0x51, 0x53, 0xC8, 0x7A, 0xBD, 0x81, 0xC5,
                             0x1E, 0xD1, 0x4E, 0x8A, 0xAF, 0xA1, 0xAF, 0x13,
                             0x8B};

uint8_t sskr_hex[]        = {0xD9, 0x01, 0x35, 0x58, 0x25, 0x01, 0x00, 0x00,
                             0x01, 0x00, 0xFF, 0x0F, 0xBB, 0x2A, 0x8B, 0xCC,
                             0x6F, 0x00, 0xC8, 0xE6, 0x83, 0xDF, 0xB0, 0xEB,
                             0x5F, 0x1C, 0x55, 0xEF, 0x12, 0xD9, 0x4B, 0x62,
                             0x97, 0x42, 0x42, 0xDA, 0x21, 0x11, 0xBA, 0xC6,
                             0x5F, 0xAA, 0xD9, 0x01, 0x35, 0x58, 0x25, 0x01,
                             0x00, 0x00, 0x01, 0x01, 0xB4, 0x8E, 0x81, 0x9F,
                             0xBB, 0x8A, 0x1C, 0xC3, 0xCF, 0xFB, 0x10, 0xBB,
                             0xC7, 0xB7, 0x96, 0xBC, 0xBD, 0xB3, 0x4F, 0x1E,
                             0x21, 0xCE, 0x04, 0x94, 0x48, 0x1E, 0x79, 0x8C,
                             0x0D, 0x7E, 0xEA, 0xA2};

unsigned int sskr_group_descriptor[] = {2, 3};

unsigned int bolos_ux_sskr_hex_decode(unsigned char *mnemonic_hex,
                                      unsigned int mnemonic_length,
                                      unsigned int sskr_shares_count,
                                      unsigned char *output);


static void test_bip39_to_sskr(void **state) {

    const unsigned char sskr_shares[] = "tuna acid epic hard data acid able able acid able zoom bias rock door luau surf jowl able soap visa legs user puff warm hope code gyro webs brag tuna gear iced miss flew flew twin curl body road skew hope peck peck echo able tinytuna acid epic hard data acid able able acid acid quiz main lazy note rock love code scar task zero blue rock slot real mint roof ruby quad glow cook curl taco aqua meow fund cook kick luck belt knob wand oboe lava urge help exittuna acid epic hard data acid able able acid also iron calm task help warm fizz loud next skew undo ruin cash holy guru tomb fuel noon hang paid gems note curl peck yank half gala maze duty task poem drum road film brew flew trip";

    unsigned char hex_buf[sizeof(bip39_hex)];
    unsigned char sskr_words_buffer[sizeof(sskr_shares)];
    unsigned char bip39_word_buffer[sizeof(bip39_mnemonic)];

    memcpy(bip39_word_buffer, bip39_mnemonic, sizeof(bip39_word_buffer));

    assert_int_equal(bolos_ux_bip39_mnemonic_check(bip39_word_buffer,
                                                   sizeof(bip39_word_buffer) - 1), 1);
    assert_int_equal(bolos_ux_bip39_mnemonic_decode(bip39_word_buffer,
                                                    sizeof(bip39_word_buffer) - 1,
                                                    hex_buf, sizeof(hex_buf)), 1);
    assert_memory_equal(bip39_hex, hex_buf, sizeof(bip39_hex));

    uint8_t share_count;
    unsigned int sskr_words_buffer_len;

    assert_int_equal(bolos_ux_bip39_to_sskr_convert(bip39_word_buffer,
                                                    sizeof(bip39_word_buffer) - 1,
                                                    MNEMONIC_SIZE_24,
                                                    sskr_group_descriptor,
                                                    &share_count, sskr_words_buffer,
                                                    &sskr_words_buffer_len), 1);
    assert_int_equal(share_count, sskr_group_descriptor[1]);
    assert_int_equal(sskr_words_buffer_len, sizeof(sskr_shares) - 1);
    assert_string_equal(sskr_words_buffer, sskr_shares);
}

static void test_sskr_to_bip39(void **state) {
    uint8_t seed_buffer[32];
    uint8_t seed_buffer_len = bolos_ux_sskr_hex_decode(sskr_hex,
                                                       sizeof(sskr_hex),
                                                       sskr_group_descriptor[0],
                                                       seed_buffer);
    unsigned char bip39_word_buffer[sizeof(bip39_mnemonic)];
    int16_t bip39_word_buffer_len = sizeof(bip39_word_buffer);

    assert_int_equal(seed_buffer_len, sizeof(seed_buffer));
    assert_memory_equal(seed_buffer, bip39_hex, seed_buffer_len);

    int16_t buf_len = bolos_ux_bip39_mnemonic_encode(seed_buffer,
                                                     sizeof(seed_buffer),
                                                     bip39_word_buffer,
                                                     bip39_word_buffer_len);
    assert_int_equal(buf_len, bip39_word_buffer_len - 1);
    assert_memory_equal(bip39_mnemonic, bip39_word_buffer, buf_len);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_bip39_to_sskr),
        cmocka_unit_test(test_sskr_to_bip39)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}