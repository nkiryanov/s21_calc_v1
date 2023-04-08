#include "calc_internal.h"

static bool validate_length(calc_expr_t expression);
static bool validate_tokens(calc_expr_t expression);

static bool match_token(calc_expr_t expression, uint32_t *start, char *token);
static bool match_number_token(calc_expr_t expression, uint32_t *start);
static void copy_input(calc_expr_t *expression, char *input);
static void remove_spaces(char *string);
static void add_parenthesis_to_func_token(char *token);

bool validate(char *input) {
  calc_expr_t expression = EMPTY_EXPRESSION;
  
  copy_input(&expression, input);

  bool expression_valid =
      (validate_length(expression) && validate_tokens(expression));

  return expression_valid;
}

bool validate_length(calc_expr_t expression) {
  bool x = (expression.size <= 256);
  return x;
}

bool validate_tokens(calc_expr_t expression) {
  bool has_error = false;

  char valid_tokens[][10] = {FUNCTIONS, PARENTHESES, OPERATORS, VARIABLES};
  int count_tokens = COUNT_OF(valid_tokens);

  for (uint32_t start = 0; start < expression.size && !has_error;) {
    bool token_match = false;

    // Try to match number
    token_match = match_number_token(expression, &start);

    // Try to match all the possible tokens except numbers
    for (int index = 0; index < count_tokens && !token_match; ++index) {
      char *token = valid_tokens[index];
      token_match = match_token(expression, &start, token);
    }

    has_error = (token_match != true);
  }

  return (has_error == false);
}

bool match_token(calc_expr_t expression, uint32_t *start, char *token) {
  // Check is the `expression` from `start` position is matched to `token`
  // If token is matched moves the start position to `token_len`
  //    If `token` is a function it will find open parenthesis
  //            Example: `sin(` instead of `sin`
  add_parenthesis_to_func_token(token);

  uint32_t token_len = strlen(token);
  uint32_t expression_len = expression.size - *start;

  bool is_token_match = false;

  if (token_len <= expression_len &&
      strncmp(token, expression.string + *start, token_len) == 0) {
    is_token_match = true;
    *start += token_len;
  }

  return is_token_match;
}

bool match_number_token(calc_expr_t expression, uint32_t *start) {
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

void add_parenthesis_to_func_token(char *token) {
  char functions[][10] = {FUNCTIONS};
  int count_functions = COUNT_OF(functions);

   for (int i = 0; i < count_functions; ++i) {
    if (strcmp(functions[i], token) == 0) strcat(token, "(");
  }
}

void copy_input(calc_expr_t *expression, char *input) {
  uint32_t input_len = strlen(input);
  uint32_t len = 0;

  len = (input_len >= MAX_LENGTH + 10) ? MAX_LENGTH + 10 : input_len;
  strncpy(expression->string, input, len);
  remove_spaces(expression->string);

  expression->size = strlen(expression->string);
}

void remove_spaces(char *string) {
  char *result = string;

  while(*string) {
    *result = *string;
    if (*string != ' ' || *string != '\n') result++;
    string++;
  }

  while (*result) {
    *result = '\0';
    result++;
  }
}

// static bool validate_name(char *valid, char *string, int start, int end) {
//   int name_len = strlen(valid);
//   int func_name_len = end - start;

//   bool is_valid = (name_len == func_name_len &&
//                    strncmp(valid, string + start, func_name_len) == 0);

//   return is_valid;
// }

// bool validate_operator_argument(calc_expr_t expression, uint32_t start) {
//   char *substr = expression.string + start;
//   uint32_t substr_len = expression.size - start;

//   bool is_valid = false;
//   is_valid = (expression.size - start > 0);
// }

// static bool validate_operators(calc_expr_t expression) {
//   char operators[][5] = {OPERATORS};
//   int count_operators = COUNT_OF(operators);
//   bool has_error = false;

//   for (int start = 0; start < expression.size && !has_error; ++start) {
//     char *name = operators[start];
//     if (is_next_name(expression, start, name)) {
//       start += strlen(name);

//     }
//     uint32_t substr_len = expression.size - i;

//   }
// }

// bool validate_function(calc_expr_t expression) {
//   char names[][5] = {FUNC_OPERATORS, FUNCTION_NAMES};

//   int num_names = sizeof(names) / sizeof(names[0]);
//   bool has_error = false;

//   for (uint32_t start = 0; start < expression.size && !has_error; ++start) {
//     if (strchr(FUNC_LITERALS, expression.string[start])) {
//       uint32_t end = start;

//       while (strchr(FUNC_LITERALS, expression.string[++end]) &&
//              end < expression.size) {
//       }

//       bool substr_match_function = false;
//       int substr_len = end - start;

//       for (int k = 0; k < num_names && !substr_match_function; ++k) {
//         char *func_name = names[k];
//         int name_len = strlen(func_name);

//         if (name_len == substr_len &&
//             strncmp(func_name, expression.string + start, substr_len) == 0) {
//           substr_match_function = true;
//         }
//       }

//       has_error = (substr_match_function != true);
//       start = end;
//     }
//   }
//   return (has_error == false);
// }
