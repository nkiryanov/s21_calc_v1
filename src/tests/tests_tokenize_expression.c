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

static void destroy(void) { deque_destroy(&tokens); }

START_TEST(test_read_expression_and_return_true) {
  fill_expression_from_str("sin(x)*10-180");

  match = tokenize_expression(&expression, tokens);

  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 8);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, FUNCTION);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, X_VARIABLE);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
}
END_TEST

START_TEST(test_read_expression_with_spaces_between_tokens) {
  fill_expression_from_str("sin(x) * 10 - 180");

  match = tokenize_expression(&expression, tokens);

  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 8);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, FUNCTION);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, X_VARIABLE);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, OPERATOR);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, NUMBER);
}
END_TEST

START_TEST(test_return_false_and_partially_filled_deque_if_error) {
  fill_expression_from_str("sin(x) * y - 1990");

  match = tokenize_expression(&expression, tokens);

  ck_assert_int_eq(match, false);
  ck_assert_int_eq(tokens->size, 5);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, FUNCTION);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, LEFT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, X_VARIABLE);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, RIGHT_PARENTHESIS);
  ck_assert_int_eq(deque_pop_front(tokens).token_type, OPERATOR);
}
END_TEST

START_TEST(test_complex_expression_parsed_ok) {
  fill_expression_from_str("sin(x) * 0.4 - (-1990 - ((cos(x))) mod 199.29392)");

  match = tokenize_expression(&expression, tokens);

  ck_assert_int_eq(match, true);
  ck_assert_int_eq(tokens->size, 22);
}
END_TEST

Suite *make_suite_tokenize_expression(void) {
  Suite *s = suite_create("tokenize_expression suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, destroy);

  tcase_add_test(tc, test_read_expression_and_return_true);
  tcase_add_test(tc, test_read_expression_with_spaces_between_tokens);
  tcase_add_test(tc, test_return_false_and_partially_filled_deque_if_error);
  tcase_add_test(tc, test_complex_expression_parsed_ok);
  return s;
}
