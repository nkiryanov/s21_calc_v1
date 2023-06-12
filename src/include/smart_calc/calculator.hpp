#ifndef SMART_CALC_CALCULATOR_CALC_H_
#define SMART_CALC_CALCULATOR_CALC_H_

#include "imgui.h"
#include "base_calculator.hpp"

namespace SmartCalc {

class Calculator: public BaseCalculator {
  private:
    char math_expression[255] = "";
    size_t math_length = 0;
    bool is_math_valid = false;
    bool is_x_allowed = false;
    double x_value = 0.0;
    double result = 0.0;

    bool ProcessEqualButtonWithResult();
    void ProcessXValueInput();
    void DrawHelpText();

  public:
    bool *is_calc_open;

    Calculator(bool *is_window_open) {is_calc_open = is_window_open;};
    void Draw();
};


}  // namespace SmartCalc

#endif  // SMART_CALC_CALCULATOR_CALC_H_
