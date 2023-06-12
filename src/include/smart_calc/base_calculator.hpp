#ifndef SMART_CALC_BASE_CALC_H_
#define SMART_CALC_BASE_CALC_H_

#include "imgui.h"

namespace SmartCalc {

class BaseCalculator {
 protected:
  virtual bool ProcessMathInput(int input_max_len, char *math_expression,
                                size_t *math_length);
  virtual void DrawErrorMessageIfNeeded(size_t math_length, bool is_math_valid);
  virtual bool ValidateMath(const char *math_expression, bool math_length,
                            bool is_x_allowed);
};

}  // namespace SmartCalc

#endif  // SMART_CALC_BASE_CALC_H_
