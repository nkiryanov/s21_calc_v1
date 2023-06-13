#ifndef CALC_RPN_CALC_EXPRESSION_H_
#define CALC_RPN_CALC_EXPRESSION_H_

#include <stdint.h>
#include <string.h>

/**
 * @brief Store expression (chars) along with it's length
 * @param string the same input string
 * @param length the length of the string
 */
typedef struct expression {
  const char* string;
  uint32_t length;
} expression_t;


/**
 * @brief Create `expression_t` from the string.
 * @param string the initial string to transform to expression.
 */
expression_t make_expression(const char* string);

#endif  // CALC_RPN_CALC_MATH_EXPRESSION_H_
