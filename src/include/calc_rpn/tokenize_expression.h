#ifndef SRC_INCLUDE_CALC_RPN_TOKENIZE_EXPRESSION_H_
#define SRC_INCLUDE_CALC_RPN_TOKENIZE_EXPRESSION_H_

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "calc_token.h"

bool tokenize_once(const char **iter, const char *end, calc_token_t *token);

#endif  // SRC_INCLUDE_CALC_RPN_TOKENIZE_EXPRESSION_H_
