#ifndef SRC_CALC_RPN_MATCH_TOKEN_H_
#define SRC_CALC_RPN_MATCH_TOKEN_H_

#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "calc_token.h"

bool match_token(char const *token_string, calc_token_t *dst);

#endif  // SRC_CALC_RPN_MATCH_TOKEN_H_
