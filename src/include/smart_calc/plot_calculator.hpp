#ifndef SMART_CALC_PLOT_CALC_H_
#define SMART_CALC_PLOT_CALC_H_

#include "imgui.h"
#include "smart_calc/base_calculator.hpp"

namespace SmartCalc {

struct PlotAxis {
  double min_value = -10;
  double max_value = 10;
  double values[1000] = {0};
};

class PlotCalculator : public BaseCalculator {
 private:
  MathExpression math;
  PlotAxis y_axis;
  PlotAxis x_axis;

  void SetAxisValues(PlotAxis &axis);
  void ProcessXAxisScaleInput();
  void CalculateYAxisIfValid();
  void DrawPlot();
  void DrawHelpMarker();

 public:
  bool *is_plot_open;

  PlotCalculator(bool *is_window_open) {
    is_plot_open = is_window_open;
    SetAxisValues(x_axis);
    SetAxisValues(y_axis);
  };

  void Draw();
};

}  // namespace SmartCalc

#endif  // SMART_CALC_PLOT_CALC_H_
