#include "calc_rpn/tokenize_expression.h"

static double operator_add(double x, double y) { return x + y; }

static double operator_sub(double x, double y) { return x - y; }

static double operator_div(double x, double y) { return x / y; }

static double operator_mul(double x, double y) { return x * y; }

static double fmod_math_correct(double x, double y) {
  double result = fmod(x, y);

  if (result < 0 && y > 0) result += y;

  return result;
}

static void set_binary_operator(double (*operator)(double, double),
                                calc_token_t *token) {
  token->token_type = BINARY_OPERATOR;
  token->storage.operator.function = operator;

  if (operator== pow) {
    token->storage.operator.priority = HIGH_PRIORITY;
    token->storage.operator.association = RIGHT_ASSOCIATED;
  } else if (operator== fmod_math_correct || operator== operator_div ||
             operator== operator_mul) {
    token->storage.operator.priority = HIGH_PRIORITY;
    token->storage.operator.association = LEFT_ASSOCIATED;
  } else {
    token->storage.operator.priority = LOW_PRIORITY;
    token->storage.operator.association = LEFT_ASSOCIATED;
  }
}

static void set_function(double (*function)(double), calc_token_t *token) {
  token->token_type = FUNCTION;
  token->storage.function = function;
}

static bool match_str_expression(const char **iter, const char *end,
                                 const char *to_match) {
  // Try to math `to_match` with the iter
  // If so move carrige right to `to_match` length and return `true`
  bool is_matched = false;

  const char *start = *iter;
  size_t substr_length = end - start;
  size_t to_match_length = strlen(to_match);

  if (to_match_length <= substr_length &&
      strncmp(start, to_match, to_match_length) == 0) {
    is_matched = true;
    *iter += to_match_length;
  }

  return is_matched;
}

static bool skip_space_once(const char **iter, const char *end) {
  bool is_space_skipped = false;

  if (**iter == ' ' && *iter != end) {
    ++(*iter);
    is_space_skipped = true;
  }

  return is_space_skipped;
}

static bool tokenize_parenthesis(const char **iter, const char *end,
                                 calc_token_t *token) {
  bool parenthesis_matched = true;

  if (match_str_expression(iter, end, "(")) {
    token->token_type = LEFT_PARENTHESIS;
    token->storage.number = 0;
  } else if (match_str_expression(iter, end, ")")) {
    token->token_type = RIGHT_PARENTHESIS;
    token->storage.number = 0;
  } else {
    parenthesis_matched = false;
  }

  return parenthesis_matched;
}

static bool tokenize_function(const char **iter, const char *end,
                              calc_token_t *token) {
  bool function_matched = true;

  if (match_str_expression(iter, end, "cos"))
    set_function(cos, token);
  else if (match_str_expression(iter, end, "sin"))
    set_function(sin, token);
  else if (match_str_expression(iter, end, "tan"))
    set_function(tan, token);
  else if (match_str_expression(iter, end, "acos"))
    set_function(acos, token);
  else if (match_str_expression(iter, end, "asin"))
    set_function(asin, token);
  else if (match_str_expression(iter, end, "atan"))
    set_function(atan, token);
  else if (match_str_expression(iter, end, "sqrt"))
    set_function(sqrt, token);
  else if (match_str_expression(iter, end, "ln"))
    set_function(log, token);
  else if (match_str_expression(iter, end, "log"))
    set_function(log10, token);
  else
    function_matched = false;

  return function_matched;
}

static bool tokenize_binary_operator(const char **iter, const char *end,
                                     calc_token_t *token) {
  bool operator_matched = true;

  if (match_str_expression(iter, end, "+"))
    set_binary_operator(operator_add, token);
  else if (match_str_expression(iter, end, "-"))
    set_binary_operator(operator_sub, token);
  else if (match_str_expression(iter, end, "/"))
    set_binary_operator(operator_div, token);
  else if (match_str_expression(iter, end, "*"))
    set_binary_operator(operator_mul, token);
  else if (match_str_expression(iter, end, "mod"))
    set_binary_operator(fmod_math_correct, token);
  else if (match_str_expression(iter, end, "^"))
    set_binary_operator(pow, token);
  else
    operator_matched = false;

  return operator_matched;
}

static bool tokenize_number(const char **iter, const char *end,
                            calc_token_t *token) {
  // Try to tokenize `iter` as a number and save it in `token`.
  // When success move `iter` to the right just after the tokenized number.
  const char *number_start = *iter;
  const char *number_end = *iter;
  uint8_t count_points = 0;
  bool is_number_matched = false;

  while (number_end != end &&
         ((*number_end >= '0' && *number_end <= '9') || *number_end == '.')) {
    if (*number_end == '.') ++count_points;
    ++number_end;
  }

  if (number_end > number_start && *number_start != '.' &&
      *(number_end - 1) != '.' && count_points <= 1) {
    double matched_value = 0;
    char number_substr[LEN_TO_STORE_MAX_TOKENS_COUNT] = "";
    int is_double_scanned_ok = -1;

    strncpy(number_substr, number_start, number_end - number_start);

    is_double_scanned_ok = sscanf(number_substr, "%lf", &matched_value);

    if (is_double_scanned_ok == 1) {
      token->token_type = NUMBER;
      token->storage.number = matched_value;
      is_number_matched = true;
      *iter = number_end;
    }
  }

  return is_number_matched;
}

static bool tokenize_variables(const char **iter, const char *end,
                               calc_token_t *token) {
  bool is_variable_matched = false;
  const char *x_variable = "x";

  if (match_str_expression(iter, end, x_variable)) {
    token->token_type = X_VARIABLE;
    token->storage.number = 0;
    is_variable_matched = true;
  }

  return is_variable_matched;
}

static void transform_binary_to_unary_if_needed(calc_deque_t *tokens) {
  if (tokens->size == 0) return;

  calc_node_t *node = tokens->head;

  while (node != NULL) {
    if (node->token.token_type != BINARY_OPERATOR) {
      node = node->right;
      continue;
    }

    calc_node_t *left_node = node->left;
    calc_node_t *right_node = node->right;

    if (left_node == NULL) {
      node->token.token_type = UNARY_OPERATOR;
    }

    if (left_node != NULL && left_node->token.token_type == LEFT_PARENTHESIS) {
      node->token.token_type = UNARY_OPERATOR;
    }

    if (left_node != NULL && right_node != NULL) {
      enum TOKEN_TYPE left_type = left_node->token.token_type;
      enum TOKEN_TYPE right_type = right_node->token.token_type;

      if (left_type == BINARY_OPERATOR &&
          (right_type == NUMBER || right_type == X_VARIABLE ||
           right_type == FUNCTION || right_type == LEFT_PARENTHESIS)) {
        node->token.token_type = UNARY_OPERATOR;
      }
    }

    node = node->right;
  }
}

bool tokenize_once(const char **iter, const char *end, calc_token_t *token,
                   bool variable_allowed) {
  bool tokenized = false;

  tokenized = tokenize_parenthesis(iter, end, token);

  if (!tokenized) tokenized = tokenize_binary_operator(iter, end, token);
  if (!tokenized) tokenized = tokenize_function(iter, end, token);
  if (!tokenized) tokenized = tokenize_number(iter, end, token);

  if (!tokenized && variable_allowed) {
    tokenized = tokenize_variables(iter, end, token);
  }

  return tokenized;
}

bool tokenize_expression(expression_t *expression, calc_deque_t *tokens,
                         bool variable_allowed) {
  bool is_token_match;
  const char *iter = expression->string;
  const char *end = expression->string + expression->length;

  for (is_token_match = true; is_token_match != false && iter != end;) {
    if (skip_space_once(&iter, end)) continue;

    INIT_TYPE_NOT_SET_TOKEN(token);

    is_token_match = tokenize_once(&iter, end, &token, variable_allowed);

    if (is_token_match) {
      deque_push_back(tokens, token);
    }
  }

  transform_binary_to_unary_if_needed(tokens);

  return is_token_match;
}
