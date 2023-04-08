#include "calc_internal.h"

static bool validate_length(calc_expression_t expression);
static bool validate_parenthesis(calc_expression_t expression);
static bool validate_number(calc_expression_t expression);
static bool validate_function(calc_expression_t expression);

bool validate(char *string) {
  calc_expression_t expression = {.string = string, .size = strlen(string)};

  bool expression_valid =
      (validate_length(expression) && validate_parenthesis(expression) &&
       validate_number(expression) && validate_function(expression));

  return expression_valid;
}

bool validate_length(calc_expression_t expression) {
  bool x = (expression.size <= 256);
  return x;
}

bool validate_parenthesis(calc_expression_t expression) {
  bool has_error = false;
  int count_left_parentheses = 0;

  for (uint32_t i = 0; i < expression.size && !has_error; ++i) {
    if (expression.string[i] == '(') ++count_left_parentheses;
    if (expression.string[i] == ')') {
      if (count_left_parentheses == 0) has_error = true;
      if (count_left_parentheses > 0) --count_left_parentheses;
    }
  }

  has_error = (has_error || count_left_parentheses != 0);

  return (has_error == true) ? false : true;
}

bool validate_number(calc_expression_t expression) {
  bool has_error = false;
  bool prev_not_number = true;
  bool dot_found = false;

  for (uint32_t i = 0; i < expression.size && !has_error; i++) {
    char value = expression.string[i];

    if (value == '.') {
      if (prev_not_number || dot_found) has_error = true;
      dot_found = true;
      prev_not_number = true;
    } else if (value >= '0' && value <= '9') {
      prev_not_number = false;
    } else {
      prev_not_number = true;
      dot_found = false;
    }
  }

  return (has_error || (dot_found && prev_not_number)) ? false : true;
}

bool validate_function(calc_expression_t expression) {
  char names[][5] = {FUNC_OPERATORS, FUNCTION_NAMES};

  int num_names = sizeof(names) / sizeof(names[0]);
  bool has_error = false;

  for (uint32_t start = 0; start < expression.size && !has_error; ++start) {
    if (strchr(FUNC_LITERALS, expression.string[start])) {
      uint32_t end = start;

      while (strchr(FUNC_LITERALS, expression.string[++end]) &&
             end < expression.size) {
      }

      bool substr_match_function = false;
      int substr_len = end - start;

      for (int k = 0; k < num_names && !substr_match_function; ++k) {
        char *func_name = names[k];
        int name_len = strlen(func_name);

        if (name_len == substr_len &&
            strncmp(func_name, expression.string + start, substr_len) == 0) {
          substr_match_function = true;
        }
      }

      has_error = (substr_match_function != true);
      start = end;
    }
  }
  return (has_error == false);
}
