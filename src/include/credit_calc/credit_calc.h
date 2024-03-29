#ifndef CREDIT_CALC_CREDIT_CALC_H_
#define CREDIT_CALC_CREDIT_CALC_H_

#include <stdbool.h>
#include <stdint.h>

#define CREDIT_MAX_MONTHS 2400  // Enough for 200 years credit
#define CREDIT_EPS 10e-3

enum CREDIT_TYPE {
  ANNUITY = 0,
  DIFFERENTIATED = 1,
};

enum CREDIT_TERM_TYPE {
  TERM_YEARS = 0,
  TERM_MONTH = 1,
};

typedef struct credit_t {
  enum CREDIT_TYPE credit_type;
  double credit_amount;
  enum CREDIT_TERM_TYPE term_type;
  int32_t term;
  double interest_rate;
} credit_t;

typedef struct credit_monthly_payment_t {
  double payment;
  double main_part_payment;
  double tax_part_payment;
  double remaining_credit;
} credit_monthly_payment_t;

typedef struct credit_payments_t {
  credit_monthly_payment_t monthly_payments[CREDIT_MAX_MONTHS];
  int32_t month_count;
  double overpayment;
  double total_payed;
} credit_payments_t;

bool get_credit_payments(const credit_t *credit,
                                 credit_payments_t *payments);

#endif  // CREDIT_CALC_CREDIT_CALC_H_
