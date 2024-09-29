#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "testutils.h"
#include "bip39/common_bip39.h"

const unsigned char bip39_mnemonic[] = "toe priority custom gauge jacket theme arrest bargain gloom wide ill fit eagle prepare capable fish limb cigar reform other priority speak rough imitate";

const unsigned char seed[] = {0x27, 0x18, 0x6B, 0x7F, 0x5A, 0xA1, 0xD6, 0xC2,
                              0xBC, 0x81, 0xCA, 0x9A, 0xB8, 0xD4, 0x3A, 0x47,
                              0x8F, 0xDB, 0x80, 0xD5, 0x26, 0x04, 0x9D, 0x7A,
                              0x28, 0x09, 0x89, 0xCA, 0x02, 0xDA, 0x86, 0xA2,
                              0xB3, 0xB2, 0x7D, 0xD0, 0x08, 0x02, 0xA5, 0xC7,
                              0x96, 0xCA, 0x4A, 0x0E, 0x51, 0x58, 0x45, 0x66,
                              0x7D, 0xEE, 0x32, 0xE7, 0x6A, 0xED, 0x18, 0x49,
                              0x8D, 0xEA, 0x8A, 0x20, 0x61, 0xFA, 0x0D, 0x9A};

static void test_bip39(void **state) {
    uint8_t buffer[64] = {0};

    bolos_ux_bip39_mnemonic_to_seed(bip39_mnemonic,
                                    sizeof(bip39_mnemonic) - 1,
                                    buffer);

    assert_memory_equal(buffer, seed, sizeof(seed));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_bip39)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
