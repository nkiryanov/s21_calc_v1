#include <check.h>

#include "calc_rpn/tokenize_expression.h"

static bool match = false;
static char *src = "sin( cos log(x) +*^mod 18.001 x coss ln";
static char *end;
static calc_token_t token;

static void setup(void) {
  match = false;
  end = src + strlen(src);

  token.token_type = TOKEN_TYPE_NOT_SET;
  token.storage.number = 0;
}

START_TEST(test_return_true_move_iter_and_set_token_if_match) {
  const char *iter = src;

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, src + 3);  // should be moved by len of `to_match`
  ck_assert_int_eq(token.token_type, FUNCTION);
  ck_assert_ptr_eq(token.storage.function, sin);
}
END_TEST

START_TEST(test_return_false_not_change_iter_and_token_if_not_match) {
  const char *iter = src + 1;

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, false);
  ck_assert_ptr_eq(iter, src + 1);  // should not be moved
  ck_assert_int_eq(token.token_type, TOKEN_TYPE_NOT_SET);
  ck_assert_int_eq(token.storage.number, 0);
}

START_TEST(test_not_fail_if_iter_start_close_to_end_to_match) {
  const char *iter = end - 1;

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, false);
  ck_assert_ptr_eq(iter, end - 1);  // not moved
  ck_assert_int_eq(token.token_type, TOKEN_TYPE_NOT_SET);
}

START_TEST(test_match_token_if_token_match_exactly_to_the_end) {
  const char *iter = end - 2;

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, end);  // moved exactly to the end
  ck_assert_int_eq(token.token_type, FUNCTION);
  ck_assert_ptr_eq(token.storage.function, log);
}

START_TEST(test_match_add_operator_correctly) {
  const char *iter = src + 16;  // should match `+`

  match = tokenize_once(&iter, end, &token);

  double (*operator)(double, double) = token.storage.operator.function;
  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, src + 17);  // moved to right once (`+` length)
  ck_assert_int_eq(token.token_type, OPERATOR);
  ck_assert_int_eq(token.storage.operator.priority, LOW_PRIORITY);
  ck_assert_int_eq(token.storage.operator.association, LEFT_ASSOCIATED);
  ck_assert_double_eq((*operator)(2, 3), 5);  // call operator 2 + 3 = 5
}

START_TEST(test_match_mul_operator_correctly) {
  const char *iter = src + 17;  // should match `*`

  match = tokenize_once(&iter, end, &token);

  double (*operator)(double, double) = token.storage.operator.function;
  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, src + 18);  // moved to right once (`*` length)
  ck_assert_int_eq(token.token_type, OPERATOR);
  ck_assert_int_eq(token.storage.operator.priority, HIGH_PRIORITY);
  ck_assert_int_eq(token.storage.operator.association, LEFT_ASSOCIATED);
  ck_assert_double_eq(operator(2, 3), 6);  // call operator 2 * 3 = 6
}

START_TEST(test_match_pow_operator_correctly) {
  const char *iter = src + 18;  // should match `^`

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, src + 19);  // moved to right once (`^` length)
  ck_assert_int_eq(token.token_type, OPERATOR);
  ck_assert_int_eq(token.storage.operator.priority, HIGH_PRIORITY);
  ck_assert_int_eq(token.storage.operator.association, RIGHT_ASSOCIATED);
  ck_assert_ptr_eq(token.storage.operator.function, pow);
}

START_TEST(test_match_mod_operator_correctly) {
  const char *iter = src + 19;  // should match `mod`

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, src + 22);  // moved to right 3 times (`mod` length)
  ck_assert_int_eq(token.token_type, OPERATOR);
  ck_assert_int_eq(token.storage.operator.priority, HIGH_PRIORITY);
  ck_assert_int_eq(token.storage.operator.association, LEFT_ASSOCIATED);
  ck_assert_ptr_eq(token.storage.operator.function, fmod);
}

START_TEST(test_left_parenthesis_matched_ok) {
  const char *iter = src + 3;  // should match `(`

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, src + 4);  // moved to right once == `(` length
  ck_assert_int_eq(token.token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(token.storage.number, 0);
}

START_TEST(test_right_parenthesis_matched_ok) {
  const char *iter = src + 14;  // should match `)`

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, src + 15);  // moved to right once == `)` length
  ck_assert_int_eq(token.token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(token.storage.number, 0);
}

START_TEST(test_number_matched_ok) {
  const char *src = "12.303+990";
  const char *iter = src;
  const char *end = src + strlen(src);

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, src + 6);
  ck_assert_int_eq(token.token_type, NUMBER);
  ck_assert_double_eq(token.storage.number, 12.303);
}

START_TEST(test_do_not_match_number_if_two_points_found) {
  const char *src = "12.30.3";
  const char *iter = src;
  const char *end = src + strlen(src);

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, false);
  ck_assert_ptr_eq(iter, src);
}

START_TEST(test_do_not_match_number_if_number_started_from_point) {
  const char *src = ".12303";
  const char *iter = src;
  const char *end = src + strlen(src);

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, false);
  ck_assert_ptr_eq(iter, src);
}

START_TEST(test_do_not_match_number_if_number_ended_with_point) {
  const char *src = "12303.";
  const char *iter = src;
  const char *end = src + strlen(src);

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, false);
  ck_assert_ptr_eq(iter, src);
}

START_TEST(test_match_x_variable) {
  const char *src = "x";
  const char *iter = src;
  const char *end = src + strlen(src);

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, true);
  ck_assert_ptr_eq(iter, end);
  ck_assert_int_eq(token.token_type, X_VARIABLE);
  ck_assert_double_eq(token.storage.number, 0);
}

START_TEST(test_do_nothing_if_not_expected_variable_found) {
  const char *src = "y";
  const char *iter = src;
  const char *end = src + strlen(src);

  match = tokenize_once(&iter, end, &token);

  ck_assert_int_eq(match, false);
  ck_assert_ptr_eq(iter, src);
}


Suite *make_suite_tokenize_once_function(void) {
  Suite *s = suite_create("tokenize_once_function suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, NULL);

  tcase_add_test(tc, test_return_true_move_iter_and_set_token_if_match);
  tcase_add_test(tc, test_return_false_not_change_iter_and_token_if_not_match);
  tcase_add_test(tc, test_not_fail_if_iter_start_close_to_end_to_match);
  tcase_add_test(tc, test_match_token_if_token_match_exactly_to_the_end);
  tcase_add_test(tc, test_match_add_operator_correctly);
  tcase_add_test(tc, test_match_mul_operator_correctly);
  tcase_add_test(tc, test_match_pow_operator_correctly);
  tcase_add_test(tc, test_match_mod_operator_correctly);
  tcase_add_test(tc, test_left_parenthesis_matched_ok);
  tcase_add_test(tc, test_right_parenthesis_matched_ok);
  tcase_add_test(tc, test_number_matched_ok);
  tcase_add_test(tc, test_do_not_match_number_if_two_points_found);
  tcase_add_test(tc, test_do_not_match_number_if_number_started_from_point);
  tcase_add_test(tc, test_do_not_match_number_if_number_ended_with_point);
  tcase_add_test(tc, test_match_x_variable);
  tcase_add_test(tc, test_do_nothing_if_not_expected_variable_found);
  return s;
}
