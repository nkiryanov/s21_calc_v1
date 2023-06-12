#include "smart_calc/base_calculator.hpp"

extern "C" {
#include "calc_rpn/calc_rpn.h"
}

#include "imgui.h"

namespace SmartCalc {

bool BaseCalculator::ProcessMathInput(int input_max_len, char *math_expression,
                                      size_t *math_length) {
  bool is_evaluation_requested = false;

  is_evaluation_requested = ImGui::InputTextWithHint(
      "##MathExpression", "enter math expression here", math_expression,
      input_max_len, ImGuiInputTextFlags_EnterReturnsTrue);

  *math_length = strlen(math_expression);
  return is_evaluation_requested;
}

void BaseCalculator::DrawErrorMessageIfNeeded(size_t math_length,
                                              bool is_math_valid) {
  if (math_length != 0 && is_math_valid == false) {
    ImVec4 red_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    ImGui::TextColored(red_color, "The expression is not valid");
  } else {
    ImGui::NewLine();
  }
}

bool BaseCalculator::ValidateMath(const char *math_expression, bool math_length,
                                  bool is_x_allowed) {
  bool is_math_valid = false;

  if (math_length != 0) {
    is_math_valid = validate_math_expression(math_expression, is_x_allowed);
  }

  return is_math_valid;
}

}  // namespace SmartCalc
