#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include "testutils.h"
#include "bip39/common_bip39.h"
#include "sskr/common_sskr.h"

static void test_words_bip39(void **state) {
    unsigned char next_letters[27] = {0};
    size_t return_num = 0;
    unsigned char prefix[] = "ab";
    unsigned char buffer[8] = {0};

    return_num = bolos_ux_bip39_get_word_idx_starting_with((const unsigned char *) prefix, 2);
    assert_int_equal(return_num, 0);

    return_num = bolos_ux_bip39_idx_strcpy(return_num, buffer);
    assert_int_equal(return_num, 7);
    assert_string_equal((const char *) buffer, "abandon");

    return_num = bolos_ux_bip39_get_word_count_starting_with((const unsigned char *) prefix, 2);
    assert_int_equal(return_num, 10);

    return_num = bolos_ux_bip39_get_word_next_letters_starting_with((const unsigned char *) prefix, 2, next_letters);
    assert_int_equal(return_num, 6);
    assert_string_equal((const char *) next_letters, "ailosu");

    prefix[0] = 'z';
    memset(next_letters,0,sizeof(next_letters));

    return_num = bolos_ux_bip39_get_word_idx_starting_with((const unsigned char *) prefix, 1);
    assert_int_equal(return_num, 2044);

    return_num = bolos_ux_bip39_idx_strcpy(return_num, buffer);
    assert_int_equal(return_num, 5);
    assert_string_equal((const char *) buffer, "zebra");

    return_num = bolos_ux_bip39_get_word_count_starting_with((const unsigned char *) prefix, 1);
    assert_int_equal(return_num, 4);

    return_num = bolos_ux_bip39_get_word_next_letters_starting_with((const unsigned char *) prefix, 1, next_letters);
    assert_int_equal(return_num, 2);
    assert_string_equal((const char *) next_letters, "eo");
}

static void test_words_sskr(void **state) {
    unsigned char next_letters[27] = {0};
    size_t return_num = 0;
    unsigned char prefix[] = "ab";
    unsigned char buffer[5] = {0};

    return_num = bolos_ux_sskr_get_word_idx_starting_with((const unsigned char *) prefix, 2);
    assert_int_equal(return_num, 0);

    return_num = bolos_ux_sskr_idx_strcpy(return_num, buffer);
    assert_int_equal(return_num, 4);
    assert_string_equal((const char *) buffer, "able");

    return_num = bolos_ux_sskr_get_word_count_starting_with((const unsigned char *) prefix, 2);
    assert_int_equal(return_num, 1);

    return_num = bolos_ux_sskr_get_word_next_letters_starting_with((const unsigned char *) prefix, 2, next_letters);
    assert_int_equal(return_num, 1);
    assert_string_equal((const char *) next_letters, "l");

    prefix[0] = 'z';
    memset(next_letters,0,sizeof(next_letters));

    return_num = bolos_ux_sskr_get_word_idx_starting_with((const unsigned char *) prefix, 1);
    assert_int_equal(return_num, 250);

    return_num = bolos_ux_sskr_idx_strcpy(return_num, buffer);
    assert_int_equal(return_num, 4);
    assert_string_equal((const char *) buffer, "zaps");

    return_num = bolos_ux_sskr_get_word_count_starting_with((const unsigned char *) prefix, 1);
    assert_int_equal(return_num, 6);

    return_num = bolos_ux_sskr_get_word_next_letters_starting_with((const unsigned char *) prefix, 1, next_letters);
    assert_int_equal(return_num, 4);
    assert_string_equal((const char *) next_letters, "aeio");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_words_bip39),
        cmocka_unit_test(test_words_sskr)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
