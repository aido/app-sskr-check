#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include "testutils.h"
#include "common_sskr.h"

static void test_sskr_words(void **state) {
    unsigned char next_letters[27] = {0};
    size_t return_num = 0;
    unsigned char prefix[] = "ab";
    unsigned char buffer[5] = {0};

    return_num = bolos_ux_sskr_get_word_idx_starting_with((const unsigned char *) prefix, 2);
    assert_int_equal(return_num, 0);

    return_num = bolos_ux_sskr_idx_strcpy(return_num, buffer);
    assert_int_equal(return_num, 4);
    assert_string_equal(buffer, "able");

    return_num = bolos_ux_sskr_get_word_count_starting_with((const unsigned char *) prefix, 2);
    assert_int_equal(return_num, 1);

    return_num = bolos_ux_sskr_get_word_next_letters_starting_with((const unsigned char *) prefix, 2, next_letters);
    assert_int_equal(return_num, 1);
    assert_string_equal(next_letters, "l");

    prefix[0] = 'z';
    memset(next_letters,0,sizeof(next_letters));

    return_num = bolos_ux_sskr_get_word_idx_starting_with((const unsigned char *) prefix, 1);
    assert_int_equal(return_num, 250);

    return_num = bolos_ux_sskr_idx_strcpy(return_num, buffer);
    assert_int_equal(return_num, 4);
    assert_string_equal(buffer, "zaps");

    return_num = bolos_ux_sskr_get_word_count_starting_with((const unsigned char *) prefix, 1);
    assert_int_equal(return_num, 6);

    return_num = bolos_ux_sskr_get_word_next_letters_starting_with((const unsigned char *) prefix, 1, next_letters);
    assert_int_equal(return_num, 4);
    assert_string_equal(next_letters, "aeio");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_sskr_words)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
