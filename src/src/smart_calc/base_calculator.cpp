#include "smart_calc/base_calculator.hpp"

extern "C" {
#include "calc_rpn/calc_rpn.h"
}

#include "imgui.h"

namespace SmartCalc {

bool BaseCalculator::ProcessMathInput(int input_max_len, MathExpression &math) {
  bool is_evaluation_requested = false;

  is_evaluation_requested = ImGui::InputTextWithHint(
      "##MathExpression", "enter math expression here", math.expression,
      input_max_len, ImGuiInputTextFlags_EnterReturnsTrue);

  math.length = strlen(math.expression);
  return is_evaluation_requested;
}

void BaseCalculator::DrawErrorMessageIfNeeded(MathExpression &math) {
  if (math.length != 0 && math.is_valid == false) {
    ImVec4 red_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    ImGui::TextColored(red_color, "The expression is not valid");
  } else {
    ImGui::NewLine();
  }
}

void BaseCalculator::ValidateMath(MathExpression &math, bool is_x_allowed) {
  math.is_valid = false;

  if (math.length != 0) {
    math.is_valid = validate_math_expression(math.expression, is_x_allowed);
  }
}

}  // namespace SmartCalc
