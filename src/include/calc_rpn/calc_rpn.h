#ifndef CALC_RPN_CALC_RPN_H_
#define CALC_RPN_CALC_RPN_H_

#include <stdbool.h>
#include <stdint.h>

bool validate_math_expression(const char *math_string, bool variable_allowed);
double evaluate_math(const char *math_string, double x);
double evaluate_simple_math(const char *math_string);
void evaluate_math_batch(const char *math_string, const double *x_values,
                           uint32_t x_count, double *y_values);

#endif  // #define CALC_RPN_CALC_RPN_H_
