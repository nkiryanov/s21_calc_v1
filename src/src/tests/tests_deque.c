#include <check.h>

#include "calc_internal.h"

static calc_token_t token = {.value = 0.1, .priority = 1};
static calc_deque_t *node;
static calc_deque_t *ya_node;
static calc_deque_t *yya_node;

static bool is_token_equal(calc_token_t token, calc_token_t expected) {
  return (token.value == expected.value && token.priority == expected.priority);
}

static void setup(void) {
  node = NULL;
  ya_node = NULL;
  yya_node = NULL;
}

static void teardown(void) {
  if (node->head != NULL) free(node->head);
  if (node->tail != NULL) free(node->tail);

  if (node != NULL) free(node);
  if (ya_node != NULL) free(ya_node);
  if (yya_node != NULL) free(yya_node);
}

START_TEST(test_deque_init) {
  node = deque_init(token);

  ck_assert_ptr_nonnull(node);
  ck_assert_ptr_null(node->left);
  ck_assert_ptr_null(node->right);
  ck_assert_ptr_eq(*(node->head), node);
  ck_assert_ptr_eq(*(node->tail), node);
  ck_assert_int_eq(is_token_equal(node->token, token), true);
}
END_TEST

START_TEST(test_deque_push_front_to_real_head) {
  node = deque_init(token);
  calc_token_t ya_token = {.value = 10., .priority = 5};

  ya_node = deque_push_front(node, ya_token);

  ck_assert_ptr_nonnull(ya_node);
  ck_assert_ptr_null(ya_node->left);
  ck_assert_ptr_eq(ya_node->right, node);
  ck_assert_ptr_eq(ya_node->head, node->head);
  ck_assert_ptr_eq(ya_node->tail, node->tail);
  ck_assert_int_eq(is_token_equal(ya_node->token, ya_token), true);

  ck_assert_ptr_eq(node->left, ya_node);

  ck_assert_ptr_eq(*(node->head), ya_node);
  ck_assert_ptr_eq(*(node->tail), node);
}

START_TEST(test_deque_push_front_to_tail_also_works) {
  calc_token_t ya_token = {.value = 10., .priority = 5};
  calc_token_t yya_token = {.value = 20., .priority = 10};
  node = deque_init(token);
  ya_node = deque_push_front(node, ya_token);

  yya_node = deque_push_front(node, yya_token);

  ck_assert_ptr_nonnull(yya_node);
  ck_assert_ptr_null(yya_node->left);
  ck_assert_ptr_eq(yya_node->right, ya_node);
  ck_assert_ptr_eq(yya_node->head, node->head);
  ck_assert_ptr_eq(yya_node->tail, node->tail);
  ck_assert_int_eq(is_token_equal(ya_node->token, ya_token), true);

  ck_assert_ptr_eq(ya_node->left, yya_node);

  ck_assert_ptr_eq(*(node->head), yya_node);
  ck_assert_ptr_eq(*(node->tail), node);
}


Suite *make_suite_deque(void) {
  Suite *s = suite_create("calc_deque suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);

  tcase_add_checked_fixture(tc, setup, teardown);
  tcase_add_test(tc, test_deque_init);
  tcase_add_test(tc, test_deque_push_front_to_real_head);
  tcase_add_test(tc, test_deque_push_front_to_tail_also_works);

  return s;
}
