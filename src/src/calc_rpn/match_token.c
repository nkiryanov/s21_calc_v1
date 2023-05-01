#include "match_token.h"

static double operator_add(double x, double y) { return x + y; }

static double operator_sub(double x, double y) { return x - y; }

static double operator_div(double x, double y) { return x / y; }

static double operator_mul(double x, double y) { return x * y; }

bool match_token(char const *token_string, calc_token_t *token) {
  if (strcmp(token_string, "+") == 0) {
    token->token_type = OPERATOR;
    token->value.operator.priority= LOW_PRIORITY;
    token->value.operator.association = LEFT_ASSOCIATED;
    token->value.operator.operator= & operator_add;
  } else if (strcmp(token_string, "-") == 0) {
    token->token_type = OPERATOR;
    token->value.operator.priority = LOW_PRIORITY;
    token->value.operator.association = LEFT_ASSOCIATED;
    token->value.operator.operator= & operator_sub;
  } else if (strcmp(token_string, "/") == 0) {
    token->token_type = OPERATOR;
    token->value.operator.priority = HIGH_PRIORITY;
    token->value.operator.association = LEFT_ASSOCIATED;
    token->value.operator.operator= & operator_div;
  } else if (strcmp(token_string, "*") == 0) {
    token->token_type = OPERATOR;
    token->value.operator.priority = HIGH_PRIORITY;
    token->value.operator.association = LEFT_ASSOCIATED;
    token->value.operator.operator= & operator_mul;
  } else if (strcmp(token_string, "mod") == 0) {
    token->token_type = OPERATOR;
    token->value.operator.priority = HIGH_PRIORITY;
    token->value.operator.association = LEFT_ASSOCIATED;
    token->value.operator.operator= & fmod;
  }

  return true;
}
