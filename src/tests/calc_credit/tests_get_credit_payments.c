#include <check.h>

#include "credit_calc/credit_calc.h"

#define EPS 10e-2

static credit_t credit;
static credit_payments_t credit_payments;

void setup(void) {
  credit.credit_type = DIFFERENTIATED;
  credit.credit_amount = 20000.0;
  credit.term = 3;
  credit.term_type = TERM_YEARS;
  credit.interest_rate = 12;

  credit_payments.month_count = 0;
  credit_payments.overpayment = 0.0;
  credit_payments.total_payed = 0.0;

  for (int i = 0; i != MAX_PAYMENTS_COUNT; ++i) {
    credit_monthly_payment_t monthly_payment = {
        .payment = 0.0,
        .main_part_payment = 0.0,
        .tax_part_payment = 0.0,
        .remaining_credit = 0.0,
    };

    credit_payments.monthly_payments[i] = monthly_payment;
  }
}

START_TEST(test_differentiated_overall_payments) {
  bool is_valid = false;

  is_valid = get_credit_payments(&credit, &credit_payments);

  ck_assert_int_eq(is_valid, true);
  ck_assert_int_eq(credit_payments.month_count, 36);
  ck_assert_double_eq_tol(credit_payments.overpayment, 3700.0, EPS);
  ck_assert_double_eq_tol(credit_payments.total_payed, 23700.0, EPS);
}

START_TEST(test_differentiated_monthly_data) {
  get_credit_payments(&credit, &credit_payments);

  credit_monthly_payment_t first_monthly = credit_payments.monthly_payments[0];
  credit_monthly_payment_t last_monthly = credit_payments.monthly_payments[35];
  ck_assert_double_eq_tol(first_monthly.main_part_payment, 555.55, EPS);
  ck_assert_double_eq_tol(first_monthly.tax_part_payment, 200.00, EPS);
  ck_assert_double_eq_tol(first_monthly.remaining_credit, 19444.44, EPS);
  ck_assert_double_eq_tol(last_monthly.main_part_payment, 555.55, EPS);
  ck_assert_double_eq_tol(last_monthly.tax_part_payment, 5.56, EPS);
  ck_assert_double_eq_tol(last_monthly.remaining_credit, 0.0, EPS);
}

START_TEST(test_differentiated_term_in_months_calculated_ok) {
  credit.term_type = TERM_MONTH;
  credit.term = 36;

  get_credit_payments(&credit, &credit_payments);

  ck_assert_int_eq(credit_payments.month_count, 36);
  ck_assert_double_eq_tol(credit_payments.overpayment, 3700.0, EPS);
  ck_assert_double_eq_tol(credit_payments.total_payed, 23700.0, EPS);
}

START_TEST(test_return_false_if_negative_data) {
  bool is_valid = true;
  credit.credit_amount = -12;

  is_valid = get_credit_payments(&credit, &credit_payments);

  ck_assert_int_eq(is_valid, false);
}

START_TEST(test_return_false_if_not_expected_credit_type_passed) {
  bool is_valid = true;
  credit.credit_type = 5;  // Not valid

  is_valid = get_credit_payments(&credit, &credit_payments);

  ck_assert_int_eq(is_valid, false);
}

START_TEST(test_return_false_if_not_expected_credit_term_type) {
  bool is_valid = true;
  credit.term_type = 5;  // Not valid

  is_valid = get_credit_payments(&credit, &credit_payments);

  ck_assert_int_eq(is_valid, false);
}

START_TEST(test_annuity_overall_payments) {
  credit.credit_type = ANNUITY;
  bool is_valid = false;
  double eps = 1;

  is_valid = get_credit_payments(&credit, &credit_payments);

  ck_assert_int_eq(is_valid, true);
  ck_assert_int_eq(credit_payments.month_count, 36);
  ck_assert_double_eq_tol(credit_payments.overpayment, 3914.30, eps);
  ck_assert_double_eq_tol(credit_payments.total_payed, 23914.44, eps);
}

START_TEST(test_annuity_monthly_data) {
  credit.credit_type = ANNUITY;
  double eps = 1;

  get_credit_payments(&credit, &credit_payments);

  credit_monthly_payment_t first_monthly = credit_payments.monthly_payments[0];
  credit_monthly_payment_t last_monthly = credit_payments.monthly_payments[35];
  ck_assert_double_eq_tol(first_monthly.main_part_payment, 464.29, eps);
  ck_assert_double_eq_tol(first_monthly.tax_part_payment, 200.00, eps);
  ck_assert_double_eq_tol(first_monthly.remaining_credit, 19535.71, eps);
  ck_assert_double_eq_tol(last_monthly.main_part_payment, 657.71, eps);
  ck_assert_double_eq_tol(last_monthly.tax_part_payment, 6.58, eps);
  ck_assert_double_eq_tol(last_monthly.remaining_credit, 0.0, eps);
}

Suite *make_suite_get_credits_payments(void) {
  Suite *s = suite_create("get_credits_payments");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, NULL);

  tcase_add_test(tc, test_differentiated_overall_payments);
  tcase_add_test(tc, test_differentiated_monthly_data);
  tcase_add_test(tc, test_differentiated_term_in_months_calculated_ok);
  tcase_add_test(tc, test_return_false_if_negative_data);
  tcase_add_test(tc, test_return_false_if_not_expected_credit_type_passed);
  tcase_add_test(tc, test_return_false_if_not_expected_credit_term_type);
  tcase_add_test(tc, test_annuity_overall_payments);
  tcase_add_test(tc, test_annuity_monthly_data);

  return s;
}
