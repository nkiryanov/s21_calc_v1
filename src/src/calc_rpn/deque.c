#include "calc_internal.h"

static calc_deque_t *calloc_deque(void) {
  calc_deque_t *node = (calc_deque_t *)malloc(sizeof(calc_deque_t));

  if (node == NULL) {
    perror("Can't allocate memory");
    exit(0);
  }

  calc_token_t empty_token = {.value = 0, .priority = 0};

  node->head = NULL;
  node->tail = NULL;
  node->left = NULL;
  node->right = NULL;
  node->token = empty_token;

  return node;
}

static calc_deque_t **calloc_deque_ptr(void) {
  calc_deque_t **node_ptr = (calc_deque_t **)malloc(sizeof(calc_deque_t *));

  if (node_ptr == NULL) {
    perror("Can't allocate memory");
    exit(0);
  }

  *(node_ptr) = NULL;

  return node_ptr;
}

calc_deque_t *deque_init(calc_token_t token) {
  calc_deque_t *node = calloc_deque();

  node->head = calloc_deque_ptr();
  node->tail = calloc_deque_ptr();

  *(node->head) = node;
  *(node->tail) = node;

  node->left = NULL;
  node->right = NULL;
  node->token = token;

  return node;
}

calc_deque_t *deque_push_front(calc_deque_t const *node, calc_token_t token) {
  calc_deque_t *new_head = calloc_deque();
  calc_deque_t *prev_head = *(node->head);

  new_head->head = node->head;
  new_head->tail = node->tail;
  *(new_head->head) = new_head;

  new_head->left = NULL;
  new_head->right = prev_head;
  new_head->token = token;

  prev_head->left = new_head;

  return new_head;
}
