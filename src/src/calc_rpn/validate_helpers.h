#ifndef SRC_CALC_RPN_VALIDATE_HELPERS_H_
#define SRC_CALC_RPN_VALIDATE_HELPERS_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

enum TOKEN_CODE {
  LEFT_PARENTHESIS = 1,
  RIGHT_PARENTHESIS = 2,
};

#define FUNCTIONS \
  "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"
#define OPERATORS "+", "-", "*", "/", "^", "mod"
#define PARENTHESES "(", ")"
#define VARIABLES "x"

#define MAX_LENGTH 255

// Calculate array length. Thanks https://stackoverflow.com/a/4415646
#define COUNT_OF(x) \
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

typedef struct calc_expression {
  uint32_t size;
  char *string;
} calc_expr_t;

bool validate(char *string);

// Helpers
bool match_number(calc_expr_t expression, uint32_t *start);
bool match_token(calc_expr_t expression, uint32_t *start);
void skip_space(calc_expr_t expression, uint32_t *start);

#endif  // SRC_CALC_RPN_VALIDATE_HELPERS_H_
