#include <check.h>

#include "calc_rpn/calc_deque.h"

static INIT_NUMBER_TOKEN(token, 0.1);
static INIT_NUMBER_TOKEN(ya_token, 10.);
static INIT_NUMBER_TOKEN(yya_token, 12.);
static calc_deque_t *deque;

static bool is_number_tokens_equal(calc_token_t token, calc_token_t expected) {
  return (token.token_type == expected.token_type &&
          token.storage.number == expected.storage.number);
}

static void setup(void) { deque = NULL; }

static void free_deque(calc_deque_t *deque) {
  while (deque->head != NULL) {
    calc_node_t *head = deque->head;
    deque->head = head->right;
    free(head);
  }
  free(deque);
}

static void teardown(void) {
  if (deque != NULL) free_deque(deque);
}

START_TEST(test_deque_init) {
  deque = deque_init();

  ck_assert_ptr_nonnull(deque);
  ck_assert_ptr_null(deque->head);
  ck_assert_ptr_null(deque->tail);
  ck_assert_uint_eq(deque->size, 0);
}
END_TEST

START_TEST(test_deque_push_front_once) {
  deque = deque_init();

  deque_push_front(deque, token);

  ck_assert_uint_eq(deque->size, 1);
  ck_assert_ptr_eq(deque->head, deque->tail);
  ck_assert_ptr_null(deque->head->left);
  ck_assert_ptr_null(deque->head->right);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, token), true);
}

START_TEST(test_deque_push_front_twice) {
  deque = deque_init();
  deque_push_front(deque, token);

  deque_push_front(deque, ya_token);

  ck_assert_uint_eq(deque->size, 2);
  ck_assert_ptr_nonnull(deque->head);
  ck_assert_ptr_null(deque->head->left);
  ck_assert_ptr_eq(deque->head->right, deque->tail);
  ck_assert_ptr_nonnull(deque->tail);
  ck_assert_ptr_null(deque->tail->right);
  ck_assert_ptr_eq(deque->tail->left, deque->head);
  ck_assert_int_eq(is_number_tokens_equal(deque->tail->token, token), true);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, ya_token), true);
}

START_TEST(test_deque_push_front_three_times) {
  deque = deque_init();
  deque_push_front(deque, token);
  deque_push_front(deque, ya_token);

  deque_push_front(deque, yya_token);

  ck_assert_uint_eq(deque->size, 3);
  ck_assert_ptr_nonnull(deque->head);
  ck_assert_ptr_nonnull(deque->tail);
  ck_assert_int_eq(is_number_tokens_equal(deque->tail->token, token), true);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, yya_token), true);
}

START_TEST(test_deque_push_back_once) {
  deque = deque_init();

  deque_push_back(deque, token);

  ck_assert_uint_eq(deque->size, 1);
  ck_assert_ptr_eq(deque->head, deque->tail);
  ck_assert_ptr_null(deque->head->left);
  ck_assert_ptr_null(deque->head->right);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, token), true);
}

START_TEST(test_deque_push_back_twice) {
  deque = deque_init();
  deque_push_back(deque, token);

  deque_push_back(deque, ya_token);

  ck_assert_uint_eq(deque->size, 2);
  ck_assert_ptr_nonnull(deque->head);
  ck_assert_ptr_null(deque->head->left);
  ck_assert_ptr_eq(deque->head->right, deque->tail);
  ck_assert_ptr_nonnull(deque->tail);
  ck_assert_ptr_null(deque->tail->right);
  ck_assert_ptr_eq(deque->tail->left, deque->head);
  ck_assert_int_eq(is_number_tokens_equal(deque->tail->token, ya_token), true);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, token), true);
}

START_TEST(test_deque_push_back_tree_times) {
  deque = deque_init();
  deque_push_back(deque, token);
  deque_push_back(deque, ya_token);

  deque_push_back(deque, yya_token);

  ck_assert_uint_eq(deque->size, 3);
  ck_assert_ptr_nonnull(deque->head);
  ck_assert_ptr_nonnull(deque->tail);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, token), true);
  ck_assert_int_eq(is_number_tokens_equal(deque->tail->token, yya_token), true);
}

START_TEST(test_deque_pop_front) {
  deque = deque_init();
  deque_push_front(deque, token);
  deque_push_front(deque, ya_token);
  deque_push_front(deque, yya_token);

  calc_token_t popped = deque_pop_front(deque);

  ck_assert_int_eq(is_number_tokens_equal(popped, yya_token), true);
  ck_assert_uint_eq(deque->size, 2);
  ck_assert_ptr_nonnull(deque->head);
  ck_assert_ptr_nonnull(deque->tail);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, ya_token), true);
}

START_TEST(test_deque_pop_front_twice) {
  deque = deque_init();
  deque_push_front(deque, token);
  deque_push_front(deque, ya_token);
  deque_push_front(deque, yya_token);
  deque_pop_front(deque);

  calc_token_t popped = deque_pop_front(deque);

  ck_assert_int_eq(is_number_tokens_equal(popped, ya_token), true);
  ck_assert_uint_eq(deque->size, 1);
  ck_assert_ptr_nonnull(deque->head);
  ck_assert_ptr_nonnull(deque->tail);
  ck_assert_ptr_null(deque->head->right);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, token), true);
}

START_TEST(test_deque_pop_front_last_token) {
  deque = deque_init();
  deque_push_front(deque, token);

  calc_token_t popped = deque_pop_front(deque);

  ck_assert_int_eq(is_number_tokens_equal(popped, token), true);
  ck_assert_uint_eq(deque->size, 0);
  ck_assert_ptr_null(deque->head);
  ck_assert_ptr_null(deque->tail);
}

START_TEST(test_deque_pop_back) {
  deque = deque_init();
  deque_push_front(deque, token);
  deque_push_front(deque, ya_token);
  deque_push_front(deque, yya_token);

  calc_token_t popped = deque_pop_back(deque);

  ck_assert_int_eq(is_number_tokens_equal(popped, token), true);
  ck_assert_uint_eq(deque->size, 2);
  ck_assert_ptr_nonnull(deque->head);
  ck_assert_ptr_nonnull(deque->tail);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, yya_token), true);
}

START_TEST(test_deque_pop_back_twice) {
  deque = deque_init();
  deque_push_front(deque, token);
  deque_push_front(deque, ya_token);
  deque_push_front(deque, yya_token);
  deque_pop_back(deque);

  calc_token_t popped = deque_pop_back(deque);

  ck_assert_int_eq(is_number_tokens_equal(popped, ya_token), true);
  ck_assert_uint_eq(deque->size, 1);
  ck_assert_ptr_nonnull(deque->head);
  ck_assert_ptr_nonnull(deque->tail);
  ck_assert_ptr_null(deque->head->right);
  ck_assert_int_eq(is_number_tokens_equal(deque->head->token, yya_token), true);
}

START_TEST(test_deque_pop_back_last_token) {
  deque = deque_init();
  deque_push_front(deque, token);

  calc_token_t popped = deque_pop_back(deque);

  ck_assert_int_eq(is_number_tokens_equal(popped, token), true);
  ck_assert_uint_eq(deque->size, 0);
  ck_assert_ptr_null(deque->head);
  ck_assert_ptr_null(deque->tail);
}

START_TEST(test_deque_pick_front_head_token) {
  deque = deque_init();
  deque_push_back(deque, token);
  deque_push_back(deque, ya_token);

  calc_token_t picked = deque_pick_front(deque);

  ck_assert_int_eq(is_number_tokens_equal(picked, token), true);
  ck_assert_uint_eq(deque->size, 2);
}

START_TEST(test_deque_pick_back_tail_token) {
  deque = deque_init();
  deque_push_back(deque, token);
  deque_push_back(deque, ya_token);

  calc_token_t picked = deque_pick_back(deque);

  ck_assert_int_eq(is_number_tokens_equal(picked, ya_token), true);
  ck_assert_uint_eq(deque->size, 2);
}

START_TEST(test_deque_destroy_empty_deque) {
  deque = deque_init();

  deque_destroy(&deque);

  ck_assert_ptr_null(deque);
}

START_TEST(test_deque_destroy) {
  deque = deque_init();
  deque_push_back(deque, token);
  deque_push_front(deque, token);
  deque_push_back(deque, token);
  deque_push_front(deque, token);
  deque_push_back(deque, token);

  deque_destroy(&deque);

  ck_assert_ptr_null(deque);
}

START_TEST(test_deque_destroy_safe_for_null_ptr) {
  calc_deque_t *deque_null_ptr = NULL;

  deque_destroy(&deque_null_ptr);  // Should not fail

  ck_assert_ptr_null(deque_null_ptr);
}

Suite *make_suite_calc_deque(void) {
  Suite *s = suite_create("calc_deque suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, teardown);
  tcase_add_test(tc, test_deque_init);
  tcase_add_test(tc, test_deque_push_front_once);
  tcase_add_test(tc, test_deque_push_front_twice);
  tcase_add_test(tc, test_deque_push_front_three_times);
  tcase_add_test(tc, test_deque_push_back_once);
  tcase_add_test(tc, test_deque_push_back_twice);
  tcase_add_test(tc, test_deque_push_back_tree_times);
  tcase_add_test(tc, test_deque_pop_front);
  tcase_add_test(tc, test_deque_pop_front_twice);
  tcase_add_test(tc, test_deque_pop_front_last_token);
  tcase_add_test(tc, test_deque_pop_back);
  tcase_add_test(tc, test_deque_pop_back_twice);
  tcase_add_test(tc, test_deque_pop_back_last_token);
  tcase_add_test(tc, test_deque_pick_front_head_token);
  tcase_add_test(tc, test_deque_pick_back_tail_token);

  TCase *tc_destroy = tcase_create("Deque destroy tests");
  suite_add_tcase(s, tc_destroy);

  tcase_add_checked_fixture(tc_destroy, setup, NULL);
  tcase_add_test(tc_destroy, test_deque_destroy_empty_deque);
  tcase_add_test(tc_destroy, test_deque_destroy);
  tcase_add_test(tc_destroy, test_deque_destroy_safe_for_null_ptr);

  return s;
}
