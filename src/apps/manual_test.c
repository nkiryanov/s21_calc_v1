#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc_rpn/calc_token.h"
#include "calc_rpn/tokenize_expression.h"

int main() {
  const char *src = "*";
  const char **iter = &src;
  const char *end = src + strlen(src);

  calc_token_t token = {
      .token_type = TOKEN_TYPE_NOT_SET,
      .storage.number = 0,
  };

  tokenize_once(iter, end, &token);

  printf("Token type = %d\n", token.token_type);

  double y = 0;
  y = (*token.storage.operator.function)(5, 4);

  printf("return = %lf\n", y);
}
