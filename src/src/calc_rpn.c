#include "calc_rpn/calc_rpn.h"

#include "calc_rpn/calc_deque.h"
#include "calc_rpn/calc_expression.h"
#include "calc_rpn/shunting_yard.h"
#include "calc_rpn/tokenize_expression.h"

static double process_rpn(calc_deque_t *rpn, double x_value) {
  calc_deque_t *result = deque_init();

  while (rpn->size != 0) {
    calc_token_t token = deque_pop_front(rpn);

    if (token.token_type == NUMBER) deque_push_back(result, token);
    if (token.token_type == OPERATOR) {
      double (*operator)(double, double) = token.storage.operator.function;
      double second_operand = deque_pop_back(result).storage.number;
      double first_operand = deque_pop_back(result).storage.number;
      calc_token_t token_to_save = {
          .token_type = NUMBER,
          .storage.number = operator(first_operand, second_operand),
      };
      deque_push_back(result, token_to_save);
    }
    if (token.token_type == FUNCTION) {
      double (*function)(double) = token.storage.function;
      double operand = deque_pop_back(result).storage.number;
      calc_token_t token_to_save = {
          .token_type = NUMBER,
          .storage.number = function(operand),
      };
      deque_push_back(result, token_to_save);
    }
    if (token.token_type == X_VARIABLE) {
      calc_token_t token_to_save = {
          .token_type = NUMBER,
          .storage.number = x_value,
      };
      deque_push_back(result, token_to_save);
    }
  }

  double evaluated_result = deque_pop_back(result).storage.number;

  deque_destroy(&result);

  return evaluated_result;
}

double evaluate_rpn(const char *math_string) {
  expression_t expression = make_expression(math_string);
  calc_deque_t *tokens = deque_init();

  tokenize_expression(&expression, tokens);
  calc_deque_t *rpn = do_shunting_yard(tokens);
  double result = process_rpn(rpn, 0);

  deque_destroy(&rpn);
  deque_destroy(&tokens);

  return result;
}
