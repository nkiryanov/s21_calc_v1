#include "validate_helpers.h"

static bool validate_length(calc_expr_t expression);
static bool validate_expression_tokens(calc_expr_t expression);

bool validate(char *input) {
  calc_expr_t expression = {.string = input, .size = strlen(input)};

  bool is_valid;

  is_valid = validate_length(expression);
  is_valid = is_valid && validate_expression_tokens(expression);

  return is_valid;
}

bool validate_length(calc_expr_t expression) {
  bool is_length_valid = (expression.size <= 256);
  return is_length_valid;
}

bool validate_expression_tokens(calc_expr_t expression) {
  // Validate that the expression has only allowed tokens
  // that could be parsed and nothing else
  bool has_error = false;

  for (uint32_t start = 0; start < expression.size && !has_error;) {
    bool token_match = false;

    // Skip any spaces between any allowed tokens
    skip_space(expression, &start);

    // Try to match number
    token_match = match_number(expression, &start);

    // Try to match all the possible tokens except numbers
    if (!token_match) token_match = match_token(expression, &start);

    has_error = (token_match != true);
  }

  return (has_error == false);
}
