#include "credit_calc/credit_calc.h"

#include <stdbool.h>

static uint32_t get_month_remaining(const credit_t *credit) {
  uint32_t term_in_months = credit->term;
  if (credit->term_type == TERM_YEARS) term_in_months = credit->term * 12;
  return term_in_months;
}

bool get_differentiated_payments(const credit_t *credit,
                                 credit_payments_t *payments) {
  if (credit->credit_amount <= 0 || credit->credit_type != DIFFERENTIATED ||
      credit->interest_rate <= 0 || credit->term <= 0 ||
      (credit->term_type != TERM_MONTH && credit->term_type != TERM_YEARS))
    return false;

  long double month_interest_rate = credit->interest_rate / 12.0 / 100.0;
  long double remaining = credit->credit_amount;
  int32_t term_in_months = get_month_remaining(credit);
  long double main_part_payment = remaining / term_in_months;

  payments->month_count = term_in_months;
  payments->total_payed = 0.0;

  for (int i = 0; i != MAX_PAYMENTS_COUNT && remaining > CREDIT_EPS; ++i) {
    long double tax_part_payment = remaining * month_interest_rate;
    long double payment = main_part_payment + tax_part_payment;

    remaining -= main_part_payment;
    --term_in_months;

    credit_monthly_payment_t monthly_payment = {
        .main_part_payment = main_part_payment,
        .tax_part_payment = tax_part_payment,
        .payment = payment,
        .remaining_credit = remaining,
    };

    payments->monthly_payments[i] = monthly_payment;
    payments->total_payed += payment;
  }

  payments->overpayment = payments->total_payed - credit->credit_amount;

  return true;
}
