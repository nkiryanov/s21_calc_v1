#ifndef SMART_CALC_CREDIT_CALC_H_
#define SMART_CALC_CREDIT_CALC_H_

#include <cstdint>

extern "C" {
#include "credit_calc/credit_calc.h"
}

namespace SmartCalc {

class CreditCalculator {
 private:
  bool* is_credit_open;
  bool is_credit_data_valid = true;

  credit_t credit = {
      .credit_type = DIFFERENTIATED,
      .credit_amount = 20000.0,
      .term_type = TERM_YEARS,
      .term = 3,
      .interest_rate = 12,
  };
  credit_payments_t monthly_payments_data = {
      .monthly_payments = {{0.0, 0.0, 0.0, 0.0}},
      .month_count = 0,
      .overpayment = 0.0,
      .total_payed = 0.0,
  };

  bool VerifyAndCalculateCreditData();
  void DrawInputData();
  void DrawAndProceedCalculateButton();
  void DrawCalculatedResult();

 public:
  CreditCalculator(bool* is_window_open) { is_credit_open = is_window_open; }
  void Draw();
};


}  // namespace SmartCalc

#endif  // SMART_CALC_CREDIT_CALC_H_