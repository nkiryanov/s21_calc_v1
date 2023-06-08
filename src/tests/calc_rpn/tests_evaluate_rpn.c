#include <check.h>

#include "calc_rpn/calc_deque.h"
#include "calc_rpn/calc_rpn.h"
#include "calc_rpn/shunting_yard.h"
#include "calc_rpn/tokenize_expression.h"

#define EPS 10 - 7

START_TEST(test_basic_expression_calculated_correctly) {
  double result = 0;

  result = evaluate_rpn("5 + 4");

  ck_assert_double_eq_tol(result, 9.0, EPS);
}
END_TEST

START_TEST(test_complicated_expression) {
  double result = 0;

  result = evaluate_rpn("sin(199) * 456 / (34 - 14) mod 10.0 + 2^2^2");

  ck_assert_double_eq_tol(result, 25.894986, EPS);
}
END_TEST

START_TEST(test_ya_complicated_expression) {
  double result = 0;

  result = evaluate_rpn("(tan(12) + sqrt(23))^2 - cos(sin(10 mod 12 + 3) - 1)");

  ck_assert_double_eq_tol(result, 16.46880, EPS);
}
END_TEST

START_TEST(test_division_by_zero) {
  double result = 0;

  result = evaluate_rpn("10 / 0");

  ck_assert_double_infinite(result);
}
END_TEST

START_TEST(test_to_big_value) {
  double result = 0;

  result = evaluate_rpn("2^3^4^5^6");  // can't be stored in double

  ck_assert_double_infinite(result);
}
END_TEST

START_TEST(test_unary_operator_at_the_beginning) {
  double result = 0;

  result = evaluate_rpn("-sin(1)");

  ck_assert_double_eq_tol(result, -0.8414709, EPS);
}
END_TEST

START_TEST(test_unary_operator_after_parenthesis) {
  double result = 0;

  result = evaluate_rpn("2 * (-1 + 4)");

  ck_assert_double_eq_tol(result, 6, EPS);
}
END_TEST

START_TEST(test_unary_operator_after_parenthesis_with_function) {
  double result = 0;

  result = evaluate_rpn("2 * (-sin(3.142) + 4)");

  ck_assert_double_eq_tol(result, 8.000814, EPS);
}
END_TEST

Suite *make_evaluate_rpn_suite(void) {
  Suite *s = suite_create("evaluate_rpn suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, test_basic_expression_calculated_correctly);
  tcase_add_test(tc, test_complicated_expression);
  tcase_add_test(tc, test_ya_complicated_expression);
  tcase_add_test(tc, test_division_by_zero);
  tcase_add_test(tc, test_to_big_value);
  tcase_add_test(tc, test_unary_operator_at_the_beginning);
  tcase_add_test(tc, test_unary_operator_after_parenthesis);
  tcase_add_test(tc, test_unary_operator_after_parenthesis_with_function);

  return s;
}
