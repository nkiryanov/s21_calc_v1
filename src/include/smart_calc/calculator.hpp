#ifndef SMART_CALC_CALCULATOR_CALC_H_
#define SMART_CALC_CALCULATOR_CALC_H_

#include "imgui.h"
#include "base_calculator.hpp"

namespace SmartCalc {

class Calculator: public BaseCalculator {
  private:
    bool *is_calc_open;
    MathExpression math;
    bool is_x_allowed = false;
    double x_value = 0.0;
    double result = 0.0;

    bool ProcessEqualButtonWithResult();
    void ProcessXValueInput();
    void DrawHelpText();

  public:

    Calculator(bool *is_window_open) {is_calc_open = is_window_open;};
    void Draw();
};


}  // namespace SmartCalc

#endif  // SMART_CALC_CALCULATOR_CALC_H_
