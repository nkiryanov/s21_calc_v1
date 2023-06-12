#include "smart_calc/plot_calculator.hpp"

extern "C" {
#include "calc_rpn/calc_rpn.h"
}

#include <cmath>

#include "imgui.h"
#include "implot.h"

namespace SmartCalc {

void PlotCalculator::SetAxisValues(PlotAxis &axis) {
  double step = (axis.max_value - axis.min_value) / 1000.0;
  double value = axis.min_value;

  for (int i = 0; i != IM_ARRAYSIZE(axis.values); ++i) {
    axis.values[i] = value;
    value += step;
  }
}

void PlotCalculator::DrawHelpMarker() {
  ImGui::SameLine();
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) &&
      ImGui::BeginTooltip()) {
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(
        "Same rules as for Calculator here.\n"
        "If have troubles please review it.");
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

void PlotCalculator::ProcessXAxisScaleInput() {
  bool is_edit = false;

  ImGui::SeparatorText("Calculate plot values for x between:");
  ImGui::SetNextItemWidth(200);
  is_edit |= ImGui::InputDouble("Left X", &(x_axis.min_value), 1, 50.0);
  ImGui::SameLine();
  ImGui::Dummy(ImVec2(50, 0));
  ImGui::SameLine();
  ImGui::SetNextItemWidth(200);
  is_edit |= ImGui::InputDouble("Right X", &(x_axis.max_value), 1, 50.0);

  if (is_edit) SetAxisValues(x_axis);
}

void PlotCalculator::CalculateYAxisIfValid() {
  if (math.is_valid) {
    int count = IM_ARRAYSIZE(x_axis.values);
    double *x_values = (double *)x_axis.values;
    double *y_values = (double *)y_axis.values;
    evaluate_math_batch(math.expression, x_values, count, y_values);
  }
}

void PlotCalculator::DrawPlot() {
  int count = IM_ARRAYSIZE(x_axis.values);
  ImPlotLineFlags flag = ImPlotLineFlags_SkipNaN;

  ImPlot::BeginPlot("##Draw Plot", ImVec2(-1, -1));
  ImPlot::PlotLine("##Draw Plot", x_axis.values, y_axis.values, count, flag);
  ImPlot::EndPlot();
}

void PlotCalculator::Draw() {
  ImGui::SetNextWindowPos(ImVec2(570, 10), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(700, 560), ImGuiCond_FirstUseEver);

  ImGui::Begin("Calculate Plot", is_plot_open);
  ImGui::Text("Expression:");
  ImGui::SameLine();
  ProcessMathInput(IM_ARRAYSIZE(math.expression), math);
  DrawHelpMarker();

  ImGui::Dummy(ImVec2(80, 0));
  ImGui::SameLine();
  DrawErrorMessageIfNeeded(math);

  ProcessXAxisScaleInput();
  DrawPlot();

  // The step done the last but it stores the state object and it
  // will be used on next iteration
  ValidateMath(math, true);
  CalculateYAxisIfValid();

  ImGui::End();
}

}  // namespace SmartCalc
