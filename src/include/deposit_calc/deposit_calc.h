#ifndef DEPOSIT_CALC_CREDIT_CALC_H_
#define DEPOSIT_CALC_CREDIT_CALC_H_

#define DEPOSIT_MAX_MONTHS 2400  // Enough for 200 years credit

#include <stdbool.h>
#include <stdint.h>

enum DEPOSIT_PAYMENT_FREQUENCY {
  DEPOSIT_FREQUENCY_YEARS = 0,
  DEPOSIT_FREQUENCY_MONTH = 1,
};

typedef struct deposit_t {
  double initial_amount;
  int32_t term;
  double interest_rate;
  double tax_rate;
  bool is_capitalized;
  enum DEPOSIT_PAYMENT_FREQUENCY payment_frequency;
  double how_much_replenished;
  double how_much_withdraw;
} deposit_t;

typedef struct deposit_earned_t {
  double earned_amount;
  double tax_amount;
  double final_amount;
} deposit_earned_t;

bool get_deposit_payments(const deposit_t *deposit, deposit_earned_t *earned);

#endif  // DEPOSIT_CALC_CREDIT_CALC_H_
