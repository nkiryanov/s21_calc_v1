#include <check.h>

#include "calc_rpn/shunting_yard.h"
#include "calc_rpn/tokenize_expression.h"

calc_deque_t *math_tokens;
calc_deque_t *rpn;

static void setup(void) {
  math_tokens = deque_init();
  rpn = NULL;
}

static void teardown(void) {
  deque_destroy(&math_tokens);
  deque_destroy(&rpn);
}

static void fulfill_tokens_from_string(const char* string) {
  expression_t str_expression;

  str_expression.string = string;
  str_expression.length = strlen(string);

  tokenize_expression(&str_expression, math_tokens);
}

START_TEST(test_simple_expression_conversion) {
  fulfill_tokens_from_string("2 / (3 + 2) * 5");

  rpn = do_shunting_yard(math_tokens);

  ck_assert_int_eq(rpn->size, 7);
}
END_TEST

Suite* make_shunting_yard_suite(void) {
  Suite* s = suite_create("shunting yard suite");
  TCase* tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, teardown);

  tcase_add_test(tc, test_simple_expression_conversion);

  return s;
}
