#include "validate_helpers.h"

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

bool match_tokens(calc_expr_t expression, uint32_t *start, char tokens[][10],
                  uint32_t count_tokens) {
  // Check is the `expression` from `start` position is matched to any token
  //
  // If token is matched the function moves the start position by `token_len`

  bool token_match = false;

  for (uint32_t index = 0; index < count_tokens && !token_match; ++index) {
    char *token = tokens[index];

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
