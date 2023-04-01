#include "calc_internal.h"

static calc_deque_t *calloc_deque(void) {
  calc_deque_t *node = (calc_deque_t *)malloc(sizeof(calc_deque_t));

  if (node == NULL) {
    perror("Can't allocate memory");
    exit(0);
  }

  calc_token_t empty_token = {.value = 0, .priority = 0};

  node->prev = NULL;
  node->next = NULL;
  node->token = empty_token;

  return node;
}

calc_deque_t *deque_init(calc_token_t token) {
  calc_deque_t *node = calloc_deque();

  node->prev = NULL;
  node->next = NULL;
  node->token = token;

  return node;
}
