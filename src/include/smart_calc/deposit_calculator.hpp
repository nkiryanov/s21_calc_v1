#ifndef SMART_CALC_DEPOSIT_CALC_H_
#define SMART_CALC_DEPOSIT_CALC_H_

#include <cstdint>

extern "C" {
#include "deposit_calc/deposit_calc.h"
}

namespace SmartCalc {

class DepositCalculator {
 private:
  bool* is_deposit_open;
  bool is_deposit_data_valid = true;

  deposit_t deposit = {
      .initial_amount = 10000.0,
      .term = 36,
      .interest_rate = 6.1,
      .tax_rate = 0.0,
      .is_capitalized = true,
      .payment_frequency = DEPOSIT_FREQUENCY_MONTH,
      .how_much_replenished = 0,
      .how_much_withdraw = 0,
  };

  deposit_earned_t earned = {
      .earned_amount = 0.0,
      .tax_amount = 0.0,
      .final_amount = 0.0,
  };

  bool VerifyAndCalculateDepositData();
  void DrawAndProceedCalculateButton();
  void DrawInputData();
  void DrawCalculatedResult();

 public:
  DepositCalculator(bool* is_window_open) { is_deposit_open = is_window_open; }
  void Draw();
};

}  // namespace SmartCalc

#endif  // SMART_CALC_DEPOSIT_CALC_H_