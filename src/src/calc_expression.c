#include "calc_rpn/calc_expression.h"

expression_t make_expression(const char* string) {
  expression_t expression = {
      .string = string,
      .length = strlen(string),
  };

  return expression;
}
