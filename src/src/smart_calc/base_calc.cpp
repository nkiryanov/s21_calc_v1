#include "smart_calc/base_calc.hpp"

extern "C" {
#include "calc_rpn/calc_rpn.h"
}

#include "imgui/imgui.h"

void SmartCalc::BaseCalc() {
  static bool show_base_calc = true;
  static double result = 0.0;
  static bool is_math_valid = false;
  static char math_expression[255] = "";

  if (show_base_calc == false) return;

  ImGui::Begin("Calculator");
  ImGui::SeparatorText("Multiply it!");

  ImGui::InputTextWithHint("=", "enter text here", math_expression,
                           IM_ARRAYSIZE(math_expression));
  ImGui::SameLine();
  ImGui::Text("%lf", result);


  if (strlen(math_expression) != 0) {
    is_math_valid = validate_math_expression(math_expression);
  }

  if (is_math_valid == false) {
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "The expression is not valid");
  }

  if (ImGui::Button(" = ", ImVec2(70, 20)) && is_math_valid) {
    result = evaluate_rpn(math_expression);
  }

  ImGui::End();
}
