#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>

#include "calc_rpn/calc_token.h"
#include "calc_rpn/tokenize_expression.h"

int main() {
  calc_token_t token = {
    .token_type = TOKEN_TYPE_NOT_SET,
    .storage.number = 0,
  };

  const char* string = "*";
  const char **iter = &string;
  const char* end = string + 1;

  tokenize_once(iter, end, &token);

  tokenize_once(iter, end, &token);
  printf("Token type = %d\n", token.token_type);
  printf("token storage = %lf\n", token.storage.number);

  printf("some value=%lf\n", sin(101202));
}
