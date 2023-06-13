#include "deposit_calc/deposit_calc.h"

#include <stdint.h>

bool validate_deposit(const deposit_t *deposit) {
  if (deposit->initial_amount < 0) return false;
  if (deposit->term <= 0) return false;
  if (deposit->interest_rate < 0) return false;
  if (deposit->tax_rate < 0) return false;
  if (deposit->how_much_replenished < 0) return false;
  if (deposit->how_much_withdraw < 0) return false;

  if (deposit->payment_frequency != DEPOSIT_FREQUENCY_MONTH &&
      deposit->payment_frequency != DEPOSIT_FREQUENCY_YEARS) {
    return false;
  }

  return true;
}

bool get_deposit_payments(const deposit_t *deposit, deposit_earned_t *earned) {
  if (!validate_deposit(deposit)) return false;

  bool is_capitalization_monthly =
      (deposit->payment_frequency == DEPOSIT_FREQUENCY_MONTH) ? true : false;

  double earned_amount = 0.0;  // It's required for not to count replenished
  double earned_but_not_capitalized = 0.0;
  double final_amount = deposit->initial_amount;

  double month_rate = deposit->interest_rate / 100.0 / 12;

  for (int i = 0; i != deposit->term; ++i) {
    double earned_this_month = final_amount * month_rate;

    earned_but_not_capitalized += earned_this_month;
    earned_amount += earned_this_month;

    if (deposit->is_capitalized && is_capitalization_monthly) {
      final_amount += earned_but_not_capitalized;
      earned_but_not_capitalized = 0.0;
    }

    if (deposit->is_capitalized && !is_capitalization_monthly) {  // yearly
      bool is_the_end_of_year = ((i + 1) % 12 == 0) ? true : false;
      if (is_the_end_of_year) {
        final_amount += earned_but_not_capitalized;
        earned_but_not_capitalized = 0;
      }
    }

    final_amount += deposit->how_much_replenished;
    final_amount -= deposit->how_much_withdraw;
  }

  final_amount += earned_but_not_capitalized;

  double taxes = earned_amount * deposit->tax_rate / 100;

  final_amount -= taxes;

  earned->earned_amount = earned_amount;
  earned->tax_amount = taxes;
  earned->final_amount = final_amount;

  return true;
}
