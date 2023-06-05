#include <check.h>

#include "calc_rpn/calc_rpn.h"

START_TEST(test_validate_parentheses_basic) {
  bool is_valid = validate_math_expression("()");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_parentheses_enclosed) {
  bool is_valid = validate_math_expression("()()()(()()(()))");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_parentheses_start_with_closed) {
  bool is_valid = validate_math_expression(")()");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_parentheses_do_not_closed) {
  bool is_valid = validate_math_expression("(");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_size_expression_len_bigger_256) {
  // Expression size has to be less or exact 256 symbols
  char *string =
      "12345678 + 12345678 + 12345678 + 12345678 + 12345678 + 12345678 + "
      "12345678 + 12345678 + 12345678 + 12345678 + 12345678 + 12345678 + "
      "12345678 + 12345678 + 12345678 + 12345678 + 12345678 + 12345678 + "
      "12345678 + 12345678 + 12345678 + 12345678 + 12345678 + 234";

  bool is_valid = validate_math_expression(string);

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_number_one_dot) {
  bool is_valid = validate_math_expression("121221.23 + 2332");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_number_two_dots_sequence) {
  bool is_valid = validate_math_expression("121221..23 + 2332");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_number_two_dots) {
  bool is_valid = validate_math_expression("121221.2.3 + 2332");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_number_dot_at_beginning) {
  bool is_valid = validate_math_expression(".121221 + 2332");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_number_dot_at_end) {
  bool is_valid = validate_math_expression("121221.");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_function_basic) {
  bool is_valid = validate_math_expression("sin(121221)");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_function_incorrect_char) {
  bool is_valid = validate_math_expression("sina(121221)");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_function_nested) {
  bool is_valid = validate_math_expression("asin(acos(log(121221)))");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

START_TEST(test_validate_function_without_opened_parenthesis) {
  bool is_valid = validate_math_expression("asin 13");

  ck_assert_int_eq(is_valid, false);
}
END_TEST

START_TEST(test_validate_operator_several_chars_length) {
  bool is_valid = validate_math_expression("12 mod 23");

  ck_assert_int_eq(is_valid, true);
}
END_TEST

Suite *make_suite_validate_math_expression(void) {
  Suite *s = suite_create("calc validate_math_expression expresion");
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
  tcase_add_test(tc, test_validate_function_without_opened_parenthesis);
  tcase_add_test(tc, test_validate_operator_several_chars_length);

  return s;
}
