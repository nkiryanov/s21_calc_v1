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

START_TEST(test_validate_number_one_dot) {
  bool is_valid = validate("121221.23 + 2332");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_number_two_dots_sequence) {
  bool is_valid = validate("121221..23 + 2332");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_number_two_dots) {
  bool is_valid = validate("121221.2.3 + 2332");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_number_dot_at_beginning) {
  bool is_valid = validate(".121221 + 2332");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_number_dot_at_end) {
  bool is_valid = validate("121221.");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_function_basic) {
  bool is_valid = validate("sin(121221)");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_function_incorrect_char) {
  bool is_valid = validate("sina(121221)");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_function_nested) {
  bool is_valid = validate("asin(acos(log(121221)))");

  ck_assert_int_eq(is_valid, true);
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
  tcase_add_test(tc, test_validate_number_one_dot);
  tcase_add_test(tc, test_validate_number_two_dots_sequence);
  tcase_add_test(tc, test_validate_number_two_dots);
  tcase_add_test(tc, test_validate_number_dot_at_beginning);
  tcase_add_test(tc, test_validate_number_dot_at_end);
  tcase_add_test(tc, test_validate_function_basic);
  tcase_add_test(tc, test_validate_function_incorrect_char);
  tcase_add_test(tc, test_validate_function_nested);

  return s;
}
