#include "calc_rpn/calc_deque.h"
#include "calc_rpn/calc_expression.h"
#include "calc_rpn/calc_rpn.h"
#include "calc_rpn/tokenize_expression.h"

static bool validate_length(expression_t* expression) {
  return (expression->length <= MAX_TOKENS_COUNT) ? true : false;
}

static bool validate_parentheses(expression_t* expression) {
  int count_left_parenthesis = 0;
  bool is_valid = true;

  for (uint32_t i = 0; i != expression->length && is_valid == true; ++i) {
    if (expression->string[i] == '(') ++count_left_parenthesis;
    if (expression->string[i] == ')') {
      if (count_left_parenthesis == 0) {
        is_valid = false;
      } else {
        --count_left_parenthesis;
      }
    }
  }

  return (is_valid == true && count_left_parenthesis == 0) ? true : false;
}

static bool is_right_node_token_left_parenthesis(calc_node_t* node) {
  return (node->right != NULL &&
          node->right->token.token_type == LEFT_PARENTHESIS)
             ? true
             : false;
}

static bool validate_function_parentheses(const calc_deque_t* tokens) {
  calc_node_t* node = tokens->head;
  bool is_valid = true;

  while (node != NULL && is_valid == true) {
    calc_token_t token = node->token;

    if (token.token_type == FUNCTION) {
      is_valid = is_right_node_token_left_parenthesis(node);
    }

    node = node->right;
  }

  return is_valid;
}

bool validate_math_expression(const char* math_string) {
  bool is_valid = false;
  expression_t expression = make_expression(math_string);
  calc_deque_t* tokens = deque_init();

  is_valid = validate_length(&expression) &&
             validate_parentheses(&expression) &&
             tokenize_expression(&expression, tokens) &&
             validate_function_parentheses(tokens);

  deque_destroy(&tokens);

  return is_valid;
}
