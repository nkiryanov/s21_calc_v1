#ifndef SRC_INCLUDE_CALC_RPN_CALC_TOKEN_H_
#define SRC_INCLUDE_CALC_RPN_CALC_TOKEN_H_

#include <stdint.h>

#define FUNCTIONS \
  "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"
#define OPERATORS "+", "-", "*", "/", "^", "mod"
#define PARENTHESES "(", ")"
#define VARIABLES "x"

#define MAX_TOKEN_LENGTH 255

enum TOKEN_TYPE {
  TOKEN_TYPE_NOT_SET = 0,
  NUMBER = 1,
  LEFT_PARENTHESIS = 2,
  RIGHT_PARENTHESIS = 3,
  FUNCTION = 4,
  OPERATOR = 5,
  X_VARIABLE = 6,
};

enum OPERATOR_ASSOCIATION {
  LEFT_ASSOCIATED = 0,
  RIGHT_ASSOCIATED = 1,
};

enum OPERATOR_PRIORITY {
  LOW_PRIORITY = 0,
  HIGH_PRIORITY = 1,
};

typedef struct calc_operator {
  double (*function)(double, double);
  enum OPERATOR_ASSOCIATION association;
  enum OPERATOR_PRIORITY priority;
} calc_operator_t;

typedef struct calc_token {
  enum TOKEN_TYPE token_type;
  union token_value_t {
    double number;
    double (*function)(double);
    calc_operator_t operator;
  } storage;
} calc_token_t;

#define INIT_NUMBER_TOKEN(TOKEN, NUMBER_VALUE) \
  calc_token_t TOKEN = {                       \
      .token_type = NUMBER,                    \
      .storage.number = NUMBER_VALUE,          \
  }

// Calculate array length. Thanks https://stackoverflow.com/a/4415646
#define COUNT_OF(x) \
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

#endif  // SRC_INCLUDE_CALC_RPN_CALC_TOKEN_H_
