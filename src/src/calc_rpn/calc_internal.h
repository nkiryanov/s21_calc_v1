#ifndef SRC_CALC_RPN_CALC_INTERNAL_H_
#define SRC_CALC_RPN_CALC_INTERNAL_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TOKEN_CODE {
  LEFT_PARENTHESIS = 1,
  RIGHT_PARENTHESIS = 1,
};

#define FUNCTION_NAMES \
  "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"
#define FUNC_OPERATORS "mod"
#define FUNC_LITERALS "acdgilmnoqrst"

typedef struct calc_token {
  double value;
  uint8_t priority;
  uint8_t code;
} calc_token_t;

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

typedef struct calc_expression {
  uint32_t size;
  char *string;
} calc_expression_t;

// --------- Deque functions -------------- //
calc_deque_t *deque_init(void);
void deque_push_front(calc_deque_t *deque, calc_token_t token);
void deque_push_back(calc_deque_t *deque, calc_token_t token);
calc_token_t deque_pop_front(calc_deque_t *deque);
calc_token_t deque_pop_back(calc_deque_t *deque);
void deque_destroy(calc_deque_t **deque_ptr);

bool validate(char *string);

#endif  // SRC_CALC_RPN_CALC_INTERNAL_H_
