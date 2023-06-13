#ifndef CREDIT_CALC_CREDIT_CALC_H_
#define CREDIT_CALC_CREDIT_CALC_H_

#include <stdint.h>

#define MAX_PAYMENTS_COUNT 2400  // Enough for 200 years credit
#define CREDIT_EPS 10e-3

enum CREDIT_TYPE {
  ANNUITY = 0,
  DIFFERENTIATED = 1,
};

enum CREDIT_TERM_TYPE {
  YEARS = 0,
  MONTH = 1,
};

typedef struct credit_t {
  enum CREDIT_TYPE credit_type;
  double credit_amount;
  uint32_t term;
  enum CREDIT_TERM_TYPE term_type;
  uint32_t interest_rate;
} credit_t;

typedef struct credit_monthly_payment_t {
  double payment;
  double main_part_payment;
  double tax_part_payment;
  double remaining_credit;
} credit_monthly_payment_t;

typedef struct credit_payments_t {
  credit_monthly_payment_t monthly_payments[MAX_PAYMENTS_COUNT];
  uint32_t month_count;
  double overpayment;
  double total_payed;
} credit_payments_t;

void get_differentiated_payments(const credit_t *credit,
                                 credit_payments_t *payments);

#endif  // CREDIT_CALC_CREDIT_CALC_H_
