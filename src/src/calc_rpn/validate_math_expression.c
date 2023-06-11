#include "calc_rpn/calc_deque.h"
#include "calc_rpn/calc_expression.h"
#include "calc_rpn/calc_rpn.h"
#include "calc_rpn/tokenize_expression.h"

static bool validate_length(expression_t* expression) {
  uint32_t length = expression->length;
  return (length <= MAX_TOKENS_COUNT && length > 0) ? true : false;
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

static bool process_math_subexpression(calc_deque_t* numbers_stack,
                                       calc_deque_t* operators_stack) {
  // Validate and process the subexpression of math expression
  // The subexpression is expression between parentheses.
  // Examples:
  //    Expression: sin(x) - (-4 * 3)
  //    Subexpressions: -4 * 3
  //
  //    Expression: 3434 - 4 * 3
  //    Subexpressions: 3434 - 4 * 3  (same as expression)

  bool is_subexpression_valid = true;
  bool is_processing_complete = false;

  while (operators_stack->size != 0 && is_subexpression_valid == true &&
         is_processing_complete == false) {
    calc_token_t last_operator = deque_pop_back(operators_stack);

    switch (last_operator.token_type) {
      case LEFT_PARENTHESIS:
        is_processing_complete = true;
        break;
      case FUNCTION:
      case UNARY_OPERATOR:
        if (numbers_stack->size < 1) {
          is_subexpression_valid = false;
        } else {
          calc_token_t last_token = deque_pick_back(numbers_stack);

          if (last_token.token_type == LEFT_PARENTHESIS) {
            is_subexpression_valid = false;
          }
        }
        break;
      case BINARY_OPERATOR:
        if (numbers_stack->size < 2) {
          is_subexpression_valid = false;
        } else {
          calc_token_t first_last_token = deque_pop_back(numbers_stack);
          calc_token_t second_last_token = deque_pick_back(numbers_stack);

          if (first_last_token.token_type == LEFT_PARENTHESIS ||
              second_last_token.token_type == LEFT_PARENTHESIS) {
            is_subexpression_valid = false;
          }
        }
        break;
      default:
        is_subexpression_valid = false;
        break;
    }
  }

  return is_subexpression_valid;
}

static bool validate_math_correct(const calc_deque_t* tokens) {
  bool is_valid = true;

  calc_deque_t* numbers_stack = deque_init();
  calc_deque_t* operators_stack = deque_init();

  calc_node_t* node = tokens->head;

  while (node != NULL && is_valid) {
    calc_token_t node_token = node->token;

    switch (node_token.token_type) {
      case NUMBER:
      case X_VARIABLE:
        deque_push_back(numbers_stack, node_token);
        break;
      case FUNCTION:
      case LEFT_PARENTHESIS:
      case UNARY_OPERATOR:
      case BINARY_OPERATOR:
        deque_push_back(operators_stack, node_token);
        break;
      case RIGHT_PARENTHESIS:
        is_valid = process_math_subexpression(numbers_stack, operators_stack);
        break;
      default:
        is_valid = false;
        break;
    }

    node = node->right;
  }

  if (is_valid) {
    is_valid = process_math_subexpression(numbers_stack, operators_stack);
  }

  if (is_valid) {
    is_valid = (operators_stack->size == 0 && numbers_stack->size <= 1);
  }

  deque_destroy(&operators_stack);
  deque_destroy(&numbers_stack);

  return is_valid;
}

bool validate_math_expression(const char* math_string, bool variable_allowed) {
  bool is_valid = false;
  expression_t expression = make_expression(math_string);
  calc_deque_t* tokens = deque_init();

  is_valid =
      validate_length(&expression) && validate_parentheses(&expression) &&
      tokenize_expression(&expression, tokens, variable_allowed) &&
      validate_function_parentheses(tokens) && validate_math_correct(tokens);

  deque_destroy(&tokens);

  return is_valid;
}
