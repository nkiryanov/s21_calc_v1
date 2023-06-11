#include <check.h>

#include "calc_rpn/tokenize_expression.h"

static calc_deque_t *tokens;
static expression_t expression;
static bool match;

static void fill_expression_from_str(const char *string) {
  expression.string = string;
  expression.length = strlen(string);
}

static void setup(void) {
  match = false;
  tokens = deque_init();

  expression.string = NULL;
  expression.length = 0;
}

static void teardown(void) { deque_destroy(&tokens); }

START_TEST(test_read_expression_and_return_true) {
  fill_expression_from_str("sin(x)*10-180");

  match = tokenize_expression(&expression, tokens, true);

  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 8);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, FUNCTION);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, X_VARIABLE);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
}
END_TEST

START_TEST(test_read_expression_with_spaces_between_tokens) {
  fill_expression_from_str("sin(x) * 10 - 180");

  match = tokenize_expression(&expression, tokens, true);

  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 8);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, FUNCTION);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, X_VARIABLE);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
}
END_TEST

START_TEST(test_return_false_and_partially_filled_deque_if_error) {
  fill_expression_from_str("sin(x) * y - 1990");

  match = tokenize_expression(&expression, tokens, true);

  ck_assert_int_eq(match, false);
  ck_assert_int_eq(tokens->size, 5);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, FUNCTION);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, X_VARIABLE);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
}
END_TEST

START_TEST(test_complex_expression_parsed_ok) {
  fill_expression_from_str("sin(x) * 0.4 - (-1990 - ((cos(x))) mod 199.29392)");

  match = tokenize_expression(&expression, tokens, true);

  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 22);
}
END_TEST

START_TEST(test_ya_complex_expression_parsed_ok) {
  fill_expression_from_str("(sin(2 / (3+2)*5) mod 10)^2");

  match = tokenize_expression(&expression, tokens, true);

  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 18);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, FUNCTION);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
}
END_TEST

START_TEST(test_unary_minus_at_the_at_the_beginning) {
  fill_expression_from_str("-sin(1)");

  match = tokenize_expression(&expression, tokens, false);

  calc_token_t first_token = deque_pick_front(tokens);
  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 5);
  ck_assert_int_eq(first_token.token_type, UNARY_OPERATOR);
}
END_TEST

START_TEST(test_unary_minus_after_left_parenthesis) {
  fill_expression_from_str("sin(-1)");

  match = tokenize_expression(&expression, tokens, false);

  calc_token_t third_token = tokens->head->right->right->token;
  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 5);
  ck_assert_int_eq(third_token.token_type, UNARY_OPERATOR);
}
END_TEST

START_TEST(test_plus_could_be_unary_too) {
  fill_expression_from_str("+sin(1)");

  match = tokenize_expression(&expression, tokens, false);

  calc_token_t first_token = deque_pick_front(tokens);
  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 5);
  ck_assert_int_eq(first_token.token_type, UNARY_OPERATOR);
}
END_TEST

START_TEST(test_all_cases_unary_operator_handled_correctly) {
  fill_expression_from_str("-10 + -sin(x) * -(12) / -x + -5 + (-12)");

  match = tokenize_expression(&expression, tokens, true);

  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 24);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, UNARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, UNARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, FUNCTION);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, X_VARIABLE);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, UNARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, UNARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, X_VARIABLE);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, UNARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, BINARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, UNARY_OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
}
END_TEST

Suite *make_suite_tokenize_expression(void) {
  Suite *s = suite_create("tokenize_expression suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, teardown);

  tcase_add_test(tc, test_read_expression_and_return_true);
  tcase_add_test(tc, test_read_expression_with_spaces_between_tokens);
  tcase_add_test(tc, test_return_false_and_partially_filled_deque_if_error);
  tcase_add_test(tc, test_complex_expression_parsed_ok);
  tcase_add_test(tc, test_ya_complex_expression_parsed_ok);
  tcase_add_test(tc, test_unary_minus_at_the_at_the_beginning);
  tcase_add_test(tc, test_unary_minus_after_left_parenthesis);
  tcase_add_test(tc, test_plus_could_be_unary_too);
  tcase_add_test(tc, test_all_cases_unary_operator_handled_correctly);

  return s;
}
