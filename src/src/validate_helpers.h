// #ifndef SRC_CALC_RPN_VALIDATE_HELPERS_H_
// #define SRC_CALC_RPN_VALIDATE_HELPERS_H_

// #include <stdbool.h>
// #include <stdint.h>
// #include <string.h>

// #include "calc_token.h"

// #define MAX_LENGTH 255

// // Calculate array length. Thanks https://stackoverflow.com/a/4415646
// #define COUNT_OF(x) \
//   ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

// typedef struct calc_expression {
//   uint32_t size;
//   char *string;
// } calc_expr_t;

// bool validate(char *string);

// // Helpers
// void skip_space(calc_expr_t expression, uint32_t *start);
// bool match_number(calc_expr_t expression, uint32_t *start);
// bool match_tokens(calc_expr_t expression, uint32_t *start, char tokens[][10],
//                   uint32_t count_tokens);

// #endif  // SRC_CALC_RPN_VALIDATE_HELPERS_H_
