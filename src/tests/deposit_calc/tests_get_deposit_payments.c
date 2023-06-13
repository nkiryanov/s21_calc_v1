#include <check.h>

#include "deposit_calc/deposit_calc.h"

static double eps = 10e-2;

static deposit_t deposit;
static deposit_earned_t earned;

void setup(void) {
  deposit.initial_amount = 700000.0;
  deposit.term = 24;
  deposit.interest_rate = 8.7;
  deposit.tax_rate = 0;
  deposit.is_capitalized = false;
  deposit.payment_frequency = DEPOSIT_FREQUENCY_MONTH;
  deposit.how_much_replenished = 0.0;
  deposit.how_much_withdraw = 0.0;

  earned.final_amount = 0.0;
  earned.earned_amount = 0.0;
  earned.tax_amount = 0.0;
}

START_TEST(test_earned_without_capitalization) {
  bool is_valid = false;

  is_valid = get_deposit_payments(&deposit, &earned);

  ck_assert_int_eq(is_valid, true);
  ck_assert_double_eq_tol(earned.final_amount, 821800.0, eps);
  ck_assert_double_eq_tol(earned.earned_amount, 121800.0, eps);
  ck_assert_double_eq_tol(earned.tax_amount, 0.0, eps);
}

START_TEST(test_earned_with_yearly_capitalization) {
  deposit.is_capitalized = true;
  deposit.payment_frequency = DEPOSIT_FREQUENCY_YEARS;
  eps = 1;

  get_deposit_payments(&deposit, &earned);

  ck_assert_double_eq_tol(earned.final_amount, 827098.0, eps);
  ck_assert_double_eq_tol(earned.earned_amount, 127098.0, eps);
  ck_assert_double_eq_tol(earned.tax_amount, 0.0, eps);
}

START_TEST(test_earned_with_monthly_capitalization) {
  deposit.is_capitalized = true;
  eps = 1;

  get_deposit_payments(&deposit, &earned);

  ck_assert_double_eq_tol(earned.final_amount, 832516.0, eps);
  ck_assert_double_eq_tol(earned.earned_amount, 132516.0, eps);
  ck_assert_double_eq_tol(earned.tax_amount, 0.0, eps);
}

START_TEST(test_earned_with_monthly_capitalization_and_replenished) {
  deposit.how_much_replenished = 10000.0;
  eps = 2000;

  get_deposit_payments(&deposit, &earned);

  // This value is ~close to real one but in not sure about
  // 100% correct logic for monthly replenished
  ck_assert_double_eq_tol(earned.final_amount, 1083602.0, eps);
  ck_assert_double_eq_tol(earned.tax_amount, 0.0, eps);
}

START_TEST(test_return_false_if_data_negative) {
  deposit.initial_amount = -1;
  bool is_valid = true;

  is_valid = get_deposit_payments(&deposit, &earned);

  ck_assert_int_eq(is_valid, false);
}

START_TEST(test_return_false_if_payment_frequency_wrong) {
  deposit.payment_frequency = 5;  // Not possible
  bool is_valid = true;

  is_valid = get_deposit_payments(&deposit, &earned);

  ck_assert_int_eq(is_valid, false);
}

Suite *make_suite_get_deposit_payments(void) {
  Suite *s = suite_create("get_deposit_payments");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, NULL);

  tcase_add_test(tc, test_earned_without_capitalization);
  tcase_add_test(tc, test_earned_with_yearly_capitalization);
  tcase_add_test(tc, test_earned_with_monthly_capitalization);
  tcase_add_test(tc, test_earned_with_monthly_capitalization_and_replenished);
  tcase_add_test(tc, test_return_false_if_data_negative);
  tcase_add_test(tc, test_return_false_if_payment_frequency_wrong);

  return s;
}
