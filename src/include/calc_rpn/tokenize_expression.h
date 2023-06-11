#ifndef CALC_RPN_TOKENIZE_EXPRESSION_H_
#define CALC_RPN_TOKENIZE_EXPRESSION_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "calc_deque.h"
#include "calc_expression.h"
#include "calc_token.h"

bool tokenize_once(const char **iter, const char *end, calc_token_t *token, bool variable_allowed);
bool tokenize_expression(expression_t *expression, calc_deque_t *tokens, bool variable_allowed);

#endif  // CALC_RPN_TOKENIZE_EXPRESSION_H_
