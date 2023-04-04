#include "calc_internal.h"

static bool validate_length(calc_expression_t expression);
static bool validate_parenthesis(calc_expression_t expression);

bool validate(char *string) {
  calc_expression_t expression = {.string = string, .size = strlen(string)};

  bool expression_valid =
      (validate_length(expression) && validate_parenthesis(expression));

  return expression_valid;
}

bool validate_length(calc_expression_t expression) {
  bool x = (expression.size <= 256);
  return x;
}

bool validate_parenthesis(calc_expression_t expression) {
  calc_deque_t *deque = deque_init();
  bool has_error = false;

  for (uint32_t i = 0; i < expression.size && has_error == false; ++i) {
    if (expression.string[i] == '(') {
      calc_token_t token = {
          .value = 0,
          .priority = 0,
          .code = LEFT_PARENTHESIS,
      };
      deque_push_back(deque, token);
    }

    if (expression.string[i] == ')') {
      if (deque->size == 0) has_error = true;
      if (deque->size > 0) deque_pop_back(deque);
    }
  }

  has_error = (has_error || deque->size != 0);

  deque_destroy(&deque);

  return (has_error == true) ? false : true;
}
