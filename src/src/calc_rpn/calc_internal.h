#ifndef SRC_CALC_RPN_CALC_INTERNAL_H_
#define SRC_CALC_RPN_CALC_INTERNAL_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct calc_token_struct {
  double value;
  uint8_t priority;
} calc_token_t;

typedef struct calc_deque_struct {
  struct calc_deque_struct *prev;
  struct calc_deque_struct *next;
  calc_token_t token;
} calc_deque_t;

calc_deque_t *deque_init(calc_token_t token);

#endif  // SRC_CALC_RPN_CALC_INTERNAL_H_
