#ifndef CALC_RPN_CALC_EXPRESSION_H_
#define CALC_RPN_CALC_EXPRESSION_H_

#include <stdint.h>
#include <string.h>

typedef struct expression {
  const char *string;
  uint32_t length;
} expression_t;

expression_t make_expression(const char* string);

#endif  // CALC_RPN_CALC_MATH_EXPRESSION_H_
