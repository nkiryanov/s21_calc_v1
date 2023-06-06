#include <check.h>

#include "calc_rpn/shunting_yard.h"
#include "calc_rpn/tokenize_expression.h"

calc_deque_t* math_tokens;
calc_deque_t* rpn;
calc_deque_t* expected_rpn;

static void setup(void) {
  math_tokens = deque_init();
  expected_rpn = deque_init();

  rpn = NULL;
}

static void teardown(void) {
  deque_destroy(&math_tokens);
  deque_destroy(&rpn);
  deque_destroy(&expected_rpn);
}

static void fulfill_tokens_from_string(const char* string,
                                       calc_deque_t* deque_to_fulfill) {
  expression_t str_expression;

  str_expression.string = string;
  str_expression.length = strlen(string);

  tokenize_expression(&str_expression, deque_to_fulfill);
}

static bool is_equal_tokens(calc_token_t* left, calc_token_t* right) {
  if (left->token_type != right->token_type) return false;

  uint8_t token_type = left->token_type;

  if (token_type == NUMBER) {
    if (left->storage.number != right->storage.number) return false;
  }

  if (token_type == FUNCTION) {
    if (left->storage.function != right->storage.function) return false;
  }

  if (token_type == BINARY_OPERATOR || token_type == UNARY_OPERATOR) {
    calc_operator_t left_operator = left->storage.operator;
    calc_operator_t right_operator = right->storage.operator;
    if (left_operator.function != right_operator.function ||
        left_operator.association != right_operator.association ||
        left_operator.priority != right_operator.priority) {
      return false;
    }
  }

  return true;
}

static bool is_equal_deque(calc_deque_t* left, calc_deque_t* right) {
  if (left->size != right->size) return false;

  uint32_t size = left->size;
  calc_node_t* left_node = left->head;
  calc_node_t* right_node = left->head;

  for (uint32_t i = 0; i != size; ++i) {
    if (is_equal_tokens(&(left_node->token), &(right_node->token)) == false) {
      return false;
    }

    left_node = left_node->right;
    right_node = right_node->right;
  }

  return true;
}

START_TEST(test_simple_expression_conversion) {
  fulfill_tokens_from_string("2 / (3 + 2) * 5", math_tokens);
  fulfill_tokens_from_string("2 3 2 + / 5 *", expected_rpn);

  rpn = do_shunting_yard(math_tokens);

  ck_assert_int_eq(rpn->size, 7);
  ck_assert_int_eq(is_equal_deque(rpn, expected_rpn), true);
}
END_TEST


START_TEST(test_pow_converted_correctly) {
  fulfill_tokens_from_string("2 ^ 3 ^ 4", math_tokens);
  fulfill_tokens_from_string("2 3 4 ^ ^", expected_rpn);

  rpn = do_shunting_yard(math_tokens);

  ck_assert_int_eq(rpn->size, 5);
  ck_assert_int_eq(is_equal_deque(rpn, expected_rpn), true);
}
END_TEST

START_TEST(test_not_simple_expression_conversion) {
  fulfill_tokens_from_string("(sin(2 / (3+2)*5) mod 10)^2", math_tokens);
  fulfill_tokens_from_string("2 x 2 + 5 * / sin 10 mod 2 ^", expected_rpn);

  rpn = do_shunting_yard(math_tokens);

  ck_assert_int_eq(rpn->size, 12);
  ck_assert_int_eq(is_equal_deque(rpn, expected_rpn), true);
}
END_TEST

Suite* make_shunting_yard_suite(void) {
  Suite* s = suite_create("shunting yard suite");
  TCase* tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, teardown);

  tcase_add_test(tc, test_simple_expression_conversion);
  tcase_add_test(tc, test_pow_converted_correctly);
  tcase_add_test(tc, test_not_simple_expression_conversion);

  return s;
}
