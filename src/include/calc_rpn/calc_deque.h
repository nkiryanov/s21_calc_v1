/**
 * @file calc_rpn/calc_deque.h
 *
 * Custom (not optimal but more than enough for the Calculator) Deque
 * implementation
 *
 */

#ifndef CALC_RPN_CALC_DEQUE_H_
#define CALC_RPN_CALC_DEQUE_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc_token.h"

/**
 * @brief Deque's node
 * 
 * The node stores the token and the pointers to the left and right nodes
 * 
 */
typedef struct calc_node {
  struct calc_node *left;
  struct calc_node *right;
  calc_token_t token;
} calc_node_t;


/**
 * @brief The Deque
 * 
 * Store pointers to head and tail and also the size of the Deque itself
 */
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
calc_token_t deque_pick_front(calc_deque_t *deque);
calc_token_t deque_pick_back(calc_deque_t *deque);
void deque_destroy(calc_deque_t **deque_ptr);

#endif  // CALC_RPN_CALC_DEQUE_H_
