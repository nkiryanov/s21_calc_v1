#ifndef SRC_CALC_RPN_CALC_DEQUE_H_
#define SRC_CALC_RPN_CALC_DEQUE_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc_token.h"

typedef struct calc_node {
  struct calc_node *left;
  struct calc_node *right;
  calc_token_t token;
} calc_node_t;

typedef struct calc_deque {
  uint32_t size;
  calc_node_t *head;
  calc_node_t *tail;

} calc_deque_t;

// --------- Deque functions -------------- //
calc_deque_t *deque_init(void);
void deque_push_front(calc_deque_t *deque, calc_token_t token);
void deque_push_back(calc_deque_t *deque, calc_token_t token);
calc_token_t deque_pop_front(calc_deque_t *deque);
calc_token_t deque_pop_back(calc_deque_t *deque);
void deque_destroy(calc_deque_t **deque_ptr);

#endif  // SRC_CALC_RPN_CALC_DEQUE_H_
