#include <check.h>

#include "calc_internal.h"

START_TEST(test_validate_parentheses_basic) {
  bool is_valid = validate("()");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_parentheses_enclosed) {
  bool is_valid = validate("()()()(()()(()))");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_parentheses_start_with_closed) {
  bool is_valid = validate(")()");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_parentheses_do_not_closed) {
  bool is_valid = validate("(");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_size_expression_len_bigger_256) {
  // Expression size has to be less or exact 256 symbols
  char *string =
      "12345678 + 12345678 + 12345678 + 12345678 + 12345678 + 12345678 + "
      "12345678 + 12345678 + 12345678 + 12345678 + 12345678 + 12345678 + "
      "12345678 + 12345678 + 12345678 + 12345678 + 12345678 + 12345678 + "
      "12345678 + 12345678 + 12345678 + 12345678 + 12345678 + 2324";

  bool is_valid = validate(string);

  ck_assert_int_eq(is_valid, false);
}
END_TEST

Suite *make_suite_validators(void) {
  Suite *s = suite_create("calc validate expresion");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_validate_parentheses_basic);
  tcase_add_test(tc, test_validate_parentheses_enclosed);
  tcase_add_test(tc, test_validate_parentheses_start_with_closed);
  tcase_add_test(tc, test_validate_parentheses_do_not_closed);
  tcase_add_test(tc, test_validate_size_expression_len_bigger_256);

  return s;
}
