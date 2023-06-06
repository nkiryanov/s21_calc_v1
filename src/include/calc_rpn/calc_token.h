#ifndef CALC_RPN_CALC_TOKEN_H_
#define CALC_RPN_CALC_TOKEN_H_

#include <stdint.h>
#include <stdbool.h>

#define FUNCTIONS \
  "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"
#define OPERATORS "+", "-", "*", "/", "^", "mod"
#define PARENTHESES "(", ")"
#define VARIABLES "x"

#define MAX_TOKENS_COUNT 255
#define LEN_TO_STORE_MAX_TOKENS_COUNT MAX_TOKENS_COUNT + 1

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
  bool is_unary;
} calc_operator_t;

typedef struct calc_token {
  enum TOKEN_TYPE token_type;
  union token_value_t {
    double number;
    double (*function)(double);
    calc_operator_t operator;
  } storage;
} calc_token_t;

#define INIT_TYPE_NOT_SET_TOKEN(TOKEN_NAME) \
  calc_token_t TOKEN_NAME = {               \
      .token_type = TOKEN_TYPE_NOT_SET,     \
      .storage.number = 0,                  \
  }

#define INIT_NUMBER_TOKEN(TOKEN_NAME, NUMBER_VALUE) \
  calc_token_t TOKEN_NAME = {                       \
      .token_type = NUMBER,                         \
      .storage.number = NUMBER_VALUE,               \
  }

// Calculate array length. Thanks https://stackoverflow.com/a/4415646
#define COUNT_OF(x) \
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

#endif  // CALC_RPN_CALC_TOKEN_H_
