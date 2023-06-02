#include "match_token.h"

static double operator_add(double x, double y) { return x + y; }

static double operator_sub(double x, double y) { return x - y; }

static double operator_div(double x, double y) { return x / y; }

static double operator_mul(double x, double y) { return x * y; }

void set_operator(double (*operator)(double, double), calc_token_t *token) {
  token->token_type = OPERATOR;
  token->storage.operator.function = operator;

  if (operator== & pow) {
    token->storage.operator.priority = HIGH_PRIORITY;
    token->storage.operator.association = RIGHT_ASSOCIATED;
  } else if (operator== & fmod) {
    token->storage.operator.priority = HIGH_PRIORITY;
    token->storage.operator.association = LEFT_ASSOCIATED;
  } else {
    token->storage.operator.priority = LOW_PRIORITY;
    token->storage.operator.association = LEFT_ASSOCIATED;
  }
}

void set_function(double (*function)(double), calc_token_t *token) {
  token->token_type = FUNCTION;
  token->storage.function = function;
}

bool match_token(const char *token_string, calc_token_t *token) {
  bool token_matched = true;

  if (strcmp(token_string, "+") == 0) {
    set_operator(&operator_add, token);
  } else if (strcmp(token_string, "-") == 0) {
    set_operator(&operator_sub, token);
  } else if (strcmp(token_string, "/") == 0) {
    set_operator(&operator_div, token);
  } else if (strcmp(token_string, "*") == 0) {
    set_operator(&operator_mul, token);
  } else if (strcmp(token_string, "mod") == 0) {
    set_operator(&fmod, token);
  } else if (strcmp(token_string, "^") == 0) {
    set_operator(&pow, token);
  } else if (strcmp(token_string, "cos") == 0) {
    set_function(&cos, token);
  } else if (strcmp(token_string, "sin") == 0) {
    set_function(&sin, token);
  } else if (strcmp(token_string, "tan") == 0) {
    set_function(&tan, token);
  } else if (strcmp(token_string, "acos") == 0) {
    set_function(&acos, token);
  } else if (strcmp(token_string, "asin") == 0) {
    set_function(&asin, token);
  } else if (strcmp(token_string, "atan") == 0) {
    set_function(&atan, token);
  } else if (strcmp(token_string, "sqrt") == 0) {
    set_function(&sqrt, token);
  } else if (strcmp(token_string, "ln") == 0) {
    set_function(&log, token);
  } else if (strcmp(token_string, "log") == 0) {
    set_function(&log10, token);
  } else {
    token_matched = false;
  }
  return token_matched;
}
