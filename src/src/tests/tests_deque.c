#include <check.h>

#include "calc_internal.h"

static calc_token_t token = {.value = 0.1, .priority = 1};
static calc_deque_t *node;

static bool is_token_equal(calc_token_t token, calc_token_t expected) {
  return (token.value == expected.value && token.priority == expected.priority);
}

static void setup(void) { node = NULL; }

static void teardown(void) {
  if (node != NULL) free(node);
}

START_TEST(test_deque_init) {
  node = deque_init(token);

  ck_assert_ptr_nonnull(node);
  ck_assert_ptr_eq(node->head, node);
  ck_assert_ptr_eq(node->tail, node);
  ck_assert_ptr_null(node->prev);
  ck_assert_ptr_null(node->next);
  ck_assert_int_eq(is_token_equal(node->token, token), true);
}
END_TEST

Suite *make_suite_deque(void) {
  Suite *s = suite_create("calc_deque suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);

  tcase_add_checked_fixture(tc, setup, teardown);
  tcase_add_test(tc, test_deque_init);

  return s;
}
