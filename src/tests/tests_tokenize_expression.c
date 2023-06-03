#include <check.h>

#include "calc_rpn/tokenize_expression.h"

static calc_deque_t *tokens;
static expression_t expression;
static bool match;
static calc_token_t token_storage[MAX_TOKEN_LENGTH];

static void fill_expression_from_str(const char *string) {
  expression.string = string;
  expression.length = strlen(string);
}

static void set_token_storage_empty(void) {
  for (int i = 0; i != MAX_TOKEN_LENGTH; ++i) {
    token_storage[i].token_type = TOKEN_TYPE_NOT_SET;
    token_storage[i].storage.number = 0;
  }
}

static void setup(void) {
  match = false;
  tokens = deque_init();

  expression.string = NULL;
  expression.length = 0;

  set_token_storage_empty();
}

static void destroy(void) { deque_destroy(&tokens); }

START_TEST(test_read_expression_and_return_true) {
  fill_expression_from_str("sin(x)*10-180");

  match = tokenize_expression(&expression, tokens);

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

Suite *make_suite_tokenize_expression(void) {
  Suite *s = suite_create("tokenize_expression suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, destroy);

  tcase_add_test(tc, test_read_expression_and_return_true);
  return s;
}
