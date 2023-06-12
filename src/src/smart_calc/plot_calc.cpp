#include "smart_calc/plot_calc.hpp"

extern "C" {
#include "calc_rpn/calc_rpn.h"
}

#include <cmath>

#include "imgui/imgui.h"
#include "implot/implot.h"

static void SetXValues(double x_values[], int array_length, double step,
                       double x_min) {
  double x_value = x_min;

  for (int i = 0; i != array_length; ++i) {
    x_values[i] = x_value;
    x_value += step;
  }
}

void SmartCalc::PlotCalc(bool *is_window_open) {
  static char math_expression[255] = "";
  static double x_min = -10;
  static double x_max = 10;

  double step = (x_max - x_min) / 1000.0;
  double x_values[1000] = {0.0};
  double y_values[1000] = {0.0};

  SetXValues(x_values, 1000, step, x_min);

  ImGui::Begin("Plot", is_window_open);
  ImGui::Text("Expression");
  ImGui::SameLine();
  ImGui::InputText("##math expression", math_expression,
                   IM_ARRAYSIZE(math_expression),
                   ImGuiInputTextFlags_EnterReturnsTrue);

  bool is_valid = false;
  is_valid = validate_math_expression(math_expression, true);

  if (is_valid) {
    double *x_values_ptr = (double *)x_values;
    double *y_values_ptr = (double *)y_values;

    evaluate_math_batch(math_expression, x_values_ptr, 1000, y_values_ptr);

    ImPlot::BeginPlot("Plot");
    ImPlot::PlotLine("My Line Plot", x_values, y_values, 1000,
                     ImPlotLineFlags_SkipNaN);
    ImPlot::EndPlot();
  }

  // double ya_x[] = {-1, 0, 1};
  // double ya_y[] = {1, 2, 3};
  // ImPlot::BeginPlot("Ya plot");
  // ImPlot::PlotLine("##Ya plot", ya_x, ya_y, 3);
  // ImPlot::EndPlot();

  ImGui::End();
}
