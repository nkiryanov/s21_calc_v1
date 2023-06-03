// #include "match_token.h"
// #include "validate_helpers.h"

// static bool validate_length(calc_expr_t *expression);
// // static bool validate_function_parenthesis(calc_expr_t *expression);
// static bool validate_math_expression(calc_expr_t *expression);

// bool validate(char *input) {
//   calc_expr_t expression = {.string = input, .size = strlen(input)};

//   bool is_valid;

//   is_valid = validate_length(&expression) &&
//              //  validate_function_parenthesis(&expression) &&
//              validate_math_expression(&expression);

//   return is_valid;
// }

// bool validate_length(calc_expr_t *expression) {
//   return (expression->size <= 256);
// }

// // bool validate_function_parenthesis(calc_expr_t* expression) {
// //   char func_tokens[][10] = {FUNCTIONS};
// //   uint32_t count_tokens = COUNT_OF(func_tokens);
// //   bool has_error = false;

// //   for (uint32_t start = 0; start < expression->size && !has_error;) {
// //     bool function_match = false;

// //     function_match =
// //         match_tokens(expression, &start, func_tokens, count_tokens);

// //     if (function_match) {
// //       // Check that function was the last token in expression or
// //       // don not have open parenthesis after it
// //       has_error =
// //           (start == expression.size - 1 || expression.string[start] !=
// '(');
// //     } else {
// //       ++start;
// //     }
// //   }

// //   return (has_error == false);
// // }

// bool validate_math_expression(calc_expr_t *expression) {
//   // Validate that the expression has only allowed tokens
//   // that could be parsed and nothing else
//   bool has_error = false;

//   char const *iter = expression->string;
//   char const *end = expression->string + expression->size - 1;

//   while (iter != end && !has_error) {
//     bool token_match = false;

//     // Skip any spaces between any allowed tokens
//     skip_space(&expression, &iter);

//     // Try to match number
//     token_match = match_number(expression, &iter);

//     // Try to match all the possible tokens except numbers
//     if (!token_match) {
//       token_match = match_token(&iter, start, tokens, count_tokens);
//     }

//     has_error = (token_match != true);
//   }

//   return (has_error == false);
// }
