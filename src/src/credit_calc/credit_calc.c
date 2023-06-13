#include "credit_calc/credit_calc.h"

#include <math.h>
#include <stdbool.h>

static uint32_t get_month_remaining(const credit_t *credit) {
  uint32_t term_in_months = credit->term;
  if (credit->term_type == TERM_YEARS) term_in_months = credit->term * 12;
  return term_in_months;
}

static void get_differentiated_payments(const credit_t *credit,
                                        credit_payments_t *payments) {
  long double month_rate = credit->interest_rate / 12.0 / 100.0;
  long double remaining = credit->credit_amount;
  int32_t term_in_months = get_month_remaining(credit);

  long double main_part_payment = remaining / term_in_months;
  payments->month_count = term_in_months;
  payments->total_payed = 0.0;

  for (int i = 0; i != CREDIT_MAX_MONTHS && remaining > CREDIT_EPS; ++i) {
    long double tax_part_payment = remaining * month_rate;
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
}

static void get_annually_payments(const credit_t *credit,
                                  credit_payments_t *payments) {
  long double month_rate = credit->interest_rate / 12.0 / 100.0;
  long double remaining = credit->credit_amount;
  int32_t term_in_months = get_month_remaining(credit);

  payments->month_count = term_in_months;
  payments->total_payed = 0.0;

  long double annuetet =
      remaining * month_rate / (1 - pow(1 + month_rate, -term_in_months));

  for (int i = 0; i != CREDIT_MAX_MONTHS && remaining > CREDIT_EPS; ++i) {
    long double tax_part_payment = remaining * month_rate;
    long double main_part_payment = annuetet - tax_part_payment;
    remaining -= main_part_payment;

    credit_monthly_payment_t monthly_payment = {
        .main_part_payment = main_part_payment,
        .tax_part_payment = tax_part_payment,
        .payment = annuetet,
        .remaining_credit = remaining,
    };

    payments->monthly_payments[i] = monthly_payment;
    payments->total_payed += annuetet;
  }

  payments->overpayment = payments->total_payed - credit->credit_amount;
}

bool get_credit_payments(const credit_t *credit, credit_payments_t *payments) {
  if (credit->credit_amount <= 0) return false;
  if (credit->interest_rate <= 0) return false;
  if (credit->term <= 0) return false;

  if (credit->credit_type != DIFFERENTIATED && credit->credit_type != ANNUITY) {
    return false;
  }

  if (credit->term_type != TERM_MONTH && credit->term_type != TERM_YEARS) {
    return false;
  }

  bool is_credit_data_valid = false;

  switch (credit->credit_type) {
    case DIFFERENTIATED:
      get_differentiated_payments(credit, payments);
      is_credit_data_valid = true;
      break;
    case ANNUITY:
      get_annually_payments(credit, payments);
      is_credit_data_valid = true;
    default:
      break;
  }

  return is_credit_data_valid;
}
