#include "smart_calc/base_calc.hpp"

extern "C" {
#include "calc_rpn/calc_rpn.h"
}

#include "imgui/imgui.h"

void SmartCalc::BaseCalc(bool *is_window_open) {
  static double result = 0.0;
  static char math_expression[255] = "";
  static bool is_expression_valid = false;
  static bool is_x_allowed = false;
  static double x_value = 0.0;

  size_t expression_length = strlen(math_expression);
  bool is_evaluate_pressed = false;

  if (*is_window_open == false) return;

  if (expression_length != 0) {
    is_expression_valid =
        validate_math_expression(math_expression, is_x_allowed);
  }

  ImGui::Begin("Calculator", is_window_open);
  ImGui::SeparatorText("Math expression:");

  ImGui::InputTextWithHint("##MathExpression", "enter expression here",
                           math_expression, IM_ARRAYSIZE(math_expression));

  if (is_expression_valid == false) ImGui::BeginDisabled();
  ImGui::SameLine();
  is_evaluate_pressed = ImGui::Button("=", ImVec2(50, 0));
  ImGui::SameLine();
  ImGui::Text("%lf", result);
  if (is_expression_valid == false) ImGui::EndDisabled();

  if (expression_length != 0 && is_expression_valid == false) {
    ImVec4 red_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    ImGui::TextColored(red_color, "The expression is not valid");
  } else {
    ImGui::NewLine();
  }

  if (is_expression_valid && is_evaluate_pressed) {
    result = evaluate_math(math_expression, x_value);
  }

  ImGui::Checkbox("Enalbe \"x\", and set value:", &is_x_allowed);
  if (is_x_allowed == false) ImGui::BeginDisabled();
  ImGui::SameLine();
  ImGui::InputDouble("##x value", &x_value);
  if (is_x_allowed == false) ImGui::EndDisabled();

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

  ImGui::End();
}
