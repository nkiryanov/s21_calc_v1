#ifndef SRC_CALC_RPN_CALC_TOKEN_H_
#define SRC_CALC_RPN_CALC_TOKEN_H_

#include <stdint.h>

#define FUNCTIONS \
  "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"
#define OPERATORS "+", "-", "*", "/", "^", "mod"
#define PARENTHESES "(", ")"
#define VARIABLES "x"

enum TOKEN_TYPE {
  NUMBER = 0,
  LEFT_PARENTHESIS = 1,
  RIGHT_PARENTHESIS = 2,
  FUNCTION = 3,
  OPERATOR = 4,
  X_VARIABLE = 5,
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
  double (*operator)(double, double);
  enum OPERATOR_ASSOCIATION association;
  enum OPERATOR_PRIORITY priority;
} calc_operator_t;

typedef struct calc_token {
  enum TOKEN_TYPE token_type;
  union token_value_t {
    double number;
    double (*function)(double);
    calc_operator_t operator;
  } value;
} calc_token_t;

#define INIT_NUMBER_TOKEN(TOKEN, NUMBER_VALUE) \
  calc_token_t TOKEN = {                \
      .token_type = NUMBER,             \
      .value.number = NUMBER_VALUE,     \
  }

#endif  // SRC_CALC_RPN_CALC_TOKEN_H_
