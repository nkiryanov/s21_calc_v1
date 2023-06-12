#ifndef SMART_CALC_BASE_CALC_H_
#define SMART_CALC_BASE_CALC_H_

#include "imgui.h"

namespace SmartCalc {

struct MathExpression {
  char expression[255] = "";
  size_t length = 0;
  bool is_valid = 0;
};

class BaseCalculator {
 protected:
  virtual bool ProcessMathInput(int input_max_len, MathExpression &math);
  virtual void DrawErrorMessageIfNeeded(MathExpression &math);
  virtual void ValidateMath(MathExpression &math, bool is_x_allowed);
};

}  // namespace SmartCalc

#endif  // SMART_CALC_BASE_CALC_H_
