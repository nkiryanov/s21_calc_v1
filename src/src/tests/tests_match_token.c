#include <check.h>

#include "match_token.h"

static INIT_NUMBER_TOKEN(token, 0);
static bool result = false;

static void setup(void) {
  INIT_NUMBER_TOKEN(empty_number_token, 0);

  token = empty_number_token;
  result = false;
}

START_TEST(test_operator_matching) {
  result = match_token("mod", &token);

  ck_assert_int_eq(token.token_type, OPERATOR);
  ck_assert_ptr_eq(token.storage.operator.operator, & fmod);
  ck_assert_int_eq(token.storage.operator.association, LEFT_ASSOCIATED);
  ck_assert_int_eq(token.storage.operator.priority, HIGH_PRIORITY);
}
END_TEST

START_TEST(test_function_matching) {
  result = match_token("sin", &token);

  ck_assert_int_eq(token.token_type, FUNCTION);
  ck_assert_ptr_eq(token.storage.operator.operator, & sin);
}
END_TEST

Suite *make_suite_match_token(void) {
  Suite *s = suite_create("match_token suite");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, NULL);

  tcase_add_test(tc, test_operator_matching);
  tcase_add_test(tc, test_function_matching);
  return s;
}
