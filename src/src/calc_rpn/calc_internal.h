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
  struct calc_deque_struct **head;
  struct calc_deque_struct **tail;
  struct calc_deque_struct *left;
  struct calc_deque_struct *right;
  calc_token_t token;
} calc_deque_t;

calc_deque_t *deque_init(calc_token_t token);
calc_deque_t *deque_push_front(calc_deque_t const *node, calc_token_t token);

#endif  // SRC_CALC_RPN_CALC_INTERNAL_H_
