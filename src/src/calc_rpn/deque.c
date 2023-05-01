#include "calc_deque.h"

static calc_node_t *calloc_node(void) {
  calc_node_t *node = (calc_node_t *)malloc(sizeof(calc_node_t));

  if (node == NULL) {
    perror("Can't allocate memory");
    exit(0);
  }

  INIT_NUMBER_TOKEN(empty_token, 0);

  node->left = NULL;
  node->right = NULL;
  node->token = empty_token;

  return node;
}

calc_deque_t *deque_init(void) {
  calc_deque_t *deque = (calc_deque_t *)malloc(sizeof(calc_deque_t));

  if (deque == NULL) {
    perror("Can't allocate memory");
    exit(0);
  }

  deque->size = 0;
  deque->head = NULL;
  deque->tail = NULL;

  return deque;
}

void deque_push_front(calc_deque_t *deque, calc_token_t token) {
  calc_node_t *node = calloc_node();

  node->token = token;
  node->right = deque->head;

  if (deque->size != 0) deque->head->left = node;
  if (deque->size == 0) deque->tail = node;
  deque->head = node;
  deque->size++;
}

void deque_push_back(calc_deque_t *deque, calc_token_t token) {
  calc_node_t *node = calloc_node();

  node->token = token;
  node->left = deque->tail;

  if (deque->size != 0) deque->tail->right = node;
  if (deque->size == 0) deque->head = node;
  deque->tail = node;
  deque->size++;
}

calc_token_t deque_pop_front(calc_deque_t *deque) {
  calc_token_t token;
  calc_node_t *node_to_pop;

  node_to_pop = deque->head;
  token = node_to_pop->token;
  deque->head = deque->head->right;
  deque->size--;

  if (deque->size >= 1) deque->head->left = NULL;
  if (deque->size == 1) deque->tail->left = NULL;
  if (deque->size == 0) deque->tail = NULL;

  free(node_to_pop);

  return token;
}

calc_token_t deque_pop_back(calc_deque_t *deque) {
  calc_token_t token;
  calc_node_t *node_to_pop;

  node_to_pop = deque->tail;
  token = node_to_pop->token;
  deque->tail = deque->tail->left;
  deque->size--;

  if (deque->size >= 1) deque->tail->right = NULL;
  if (deque->size == 1) deque->head->right = NULL;
  if (deque->size == 0) deque->head = NULL;

  free(node_to_pop);

  return token;
}

void deque_destroy(calc_deque_t **deque_ptr) {
  calc_deque_t *deque = *deque_ptr;

  while (deque->size != 0) deque_pop_front(deque);
  free(*deque_ptr);
  *deque_ptr = NULL;
}
