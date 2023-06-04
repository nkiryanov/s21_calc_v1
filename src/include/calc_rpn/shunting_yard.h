#ifndef CALC_RPN_SHUNTING_YARD_H_
#define CALC_RPN_SHUNTING_YARD_H_

#include "calc_deque.h"
#include "calc_token.h"

calc_deque_t* do_shunting_yard(calc_deque_t* math_tokens);

#endif  // CALC_RPN_SHUNTING_YARD_H_
