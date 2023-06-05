#ifndef CALC_RPN_CALC_RPN_H_
#define CALC_RPN_CALC_RPN_H_

#include <stdbool.h>

bool validate(const char *math_string);
double evaluate_rpn(const char *math_string);

#endif  // #define CALC_RPN_CALC_RPN_H_
