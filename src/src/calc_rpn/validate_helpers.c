#include "validate_helpers.h"

static void add_parenthesis_to_func_token(char *token) {
  char functions[][10] = {FUNCTIONS};
  int count_functions = COUNT_OF(functions);

  for (int i = 0; i < count_functions; ++i) {
    if (strcmp(functions[i], token) == 0) strcat(token, "(");
  }
}

void skip_space(calc_expr_t expression, uint32_t *start) {
  while (expression.string[*start] == ' ') {
    *start += 1;
  }
}

bool match_number(calc_expr_t expression, uint32_t *start) {
  // Check is the expression started from `start` is a number
  // If is it so, moves the start position just after the number
  uint32_t end = *start;

  while ((expression.string[end] >= '0' && expression.string[end] <= '9') ||
         expression.string[end] == '.') {
    ++end;
  }

  bool token_match = (end > *start && expression.string[*start] != '.' &&
                      expression.string[end - 1] != '.');
  bool point_found = false;

  for (uint32_t i = *start; i < end && token_match; ++i) {
    if (expression.string[i] == '.') {
      if (point_found)
        token_match = false;
      else
        point_found = true;
    }
  }

  *start = end;
  return token_match;
}

bool match_token(calc_expr_t expression, uint32_t *start) {
  // Check is the `expression` from `start` position is matched to any valid
  // token (may be function, operator or parenthesis).
  //
  // If token is matched moves the start position to `token_len`
  // If `token` is a function it will find open parenthesis
  //   Example: `sin(` instead of `sin`

  char valid_tokens[][10] = {FUNCTIONS, PARENTHESES, OPERATORS, VARIABLES};
  int count_tokens = COUNT_OF(valid_tokens);
  bool token_match = false;

  for (int index = 0; index < count_tokens && !token_match; ++index) {
    char *token = valid_tokens[index];

    add_parenthesis_to_func_token(token);

    uint32_t token_len = strlen(token);
    uint32_t expression_len = expression.size - *start;

    if (token_len <= expression_len &&
        strncmp(token, expression.string + *start, token_len) == 0) {
      token_match = true;
      *start += token_len;
    }
  }

  return token_match;
}
