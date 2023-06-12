#include "smart_calc/calculator.hpp"

extern "C" {
#include "calc_rpn/calc_rpn.h"
}

#include "imgui.h"

namespace SmartCalc {

bool Calculator::ProcessEqualButtonWithResult() {
  bool is_evaluation_requested = false;

  if (math.is_valid == false) ImGui::BeginDisabled();

  ImGui::SameLine();
  is_evaluation_requested = ImGui::Button("=", ImVec2(50, 0));
  ImGui::SameLine();
  ImGui::Text("%lf", result);

  if (math.is_valid == false) ImGui::EndDisabled();

  return is_evaluation_requested;
}

void Calculator::ProcessXValueInput() {
  ImGui::Checkbox("Enalbe \"x\", and set value:", &is_x_allowed);
  if (is_x_allowed == false) ImGui::BeginDisabled();
  ImGui::SameLine();
  ImGui::SetNextItemWidth(143);
  ImGui::InputDouble("##x value", &x_value);
  if (is_x_allowed == false) ImGui::EndDisabled();
}

void Calculator::DrawHelpText() {
  ImGui::NewLine();
  ImGui::SeparatorText("How to use:");
  ImGui::Text("Write a mathematical expression the way you used to.");
  ImGui::NewLine();
  ImGui::Text("Example: sin(x) * -10 mod 5 / ln(23)^2");
  ImGui::NewLine();
  ImGui::Text("What supported:");
  ImGui::BulletText(
      "Functions: cos, sin, tan, acos, asin, atan, sqrt, ln, log");
  ImGui::BulletText("Operators: +, -, *, /, ^, mod");
  ImGui::BulletText("Parentheses: ()");
  ImGui::BulletText("Variables: x");
}

void Calculator::Draw() {
  bool is_evaluation_requested = false;

  ImGui::SetNextWindowPos(ImVec2(10, 220), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(550, 350), ImGuiCond_FirstUseEver);
  ImGui::Begin("Calculator", is_calc_open);
  ImGui::SeparatorText("Math expression:");

  is_evaluation_requested =
      Calculator::ProcessMathInput(IM_ARRAYSIZE(math.expression), math);
  is_evaluation_requested |= Calculator::ProcessEqualButtonWithResult();

  Calculator::DrawErrorMessageIfNeeded(math);
  Calculator::ProcessXValueInput();
  Calculator::DrawHelpText();

  ImGui::End();

  // This step done the last but it store it state in `Calculator` and it
  // will be used on next iteration
  ValidateMath(math, is_x_allowed);

  if (math.is_valid && is_evaluation_requested)
    result = evaluate_math(math.expression, x_value);
}

}  // namespace SmartCalc
