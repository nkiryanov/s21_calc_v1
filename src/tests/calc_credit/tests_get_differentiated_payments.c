#include <check.h>

#include "credit_calc/credit_calc.h"

#define EPS 10e-2

static credit_t credit = {
    .credit_type = DIFFERENTIATED,
    .credit_amount = 20000.0,
    .term = 3,
    .term_type = YEARS,
    .interest_rate = 12,
};

credit_payments_t credit_payments;

void setup(void) {
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

START_TEST(test_overall_payments_calculated_correctly) {
  credit_payments_t credit_payments;

  get_differentiated_payments(&credit, &credit_payments);

  ck_assert_int_eq(credit_payments.month_count, 36);
  ck_assert_double_eq_tol(credit_payments.overpayment, 3700.0, EPS);
  ck_assert_double_eq_tol(credit_payments.total_payed, 23700.0, EPS);
}

START_TEST(test_monthly_payments_calculated_correctly) {
  credit_payments_t credit_payments;

  get_differentiated_payments(&credit, &credit_payments);

  credit_monthly_payment_t first_monthly = credit_payments.monthly_payments[0];
  credit_monthly_payment_t last_monthly = credit_payments.monthly_payments[35];
  ck_assert_double_eq_tol(first_monthly.main_part_payment, 555.55, EPS);
  ck_assert_double_eq_tol(first_monthly.tax_part_payment, 200.00, EPS);
  ck_assert_double_eq_tol(first_monthly.remaining_credit, 19444.44, EPS);
  ck_assert_double_eq_tol(last_monthly.main_part_payment, 555.55, EPS);
  ck_assert_double_eq_tol(last_monthly.tax_part_payment, 5.56, EPS);
  ck_assert_double_eq_tol(last_monthly.remaining_credit, 0.0, EPS);
}

START_TEST(test_term_in_months_calculated_ok) {
  credit_payments_t credit_payments;
  credit.term_type = MONTH;
  credit.term = 36;

  get_differentiated_payments(&credit, &credit_payments);

  ck_assert_int_eq(credit_payments.month_count, 36);
  ck_assert_double_eq_tol(credit_payments.overpayment, 3700.0, EPS);
  ck_assert_double_eq_tol(credit_payments.total_payed, 23700.0, EPS);
}

Suite *make_suite_get_differentiated_payments(void) {
  Suite *s = suite_create("get_differentiated_payments");
  TCase *tc = tcase_create("Core");

  suite_add_tcase(s, tc);
  tcase_add_checked_fixture(tc, setup, NULL);

  tcase_add_test(tc, test_overall_payments_calculated_correctly);
  tcase_add_test(tc, test_monthly_payments_calculated_correctly);
  tcase_add_test(tc, test_term_in_months_calculated_ok);

  return s;
}
