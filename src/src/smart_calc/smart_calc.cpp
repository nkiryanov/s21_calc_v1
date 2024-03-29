#include "smart_calc/smart_calc.hpp"

#include <stdio.h>
#include <string.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "smart_calc/calculator.hpp"
#include "smart_calc/credit_calculator.hpp"
#include "smart_calc/deposit_calculator.hpp"
#include "smart_calc/plot_calculator.hpp"
#include "smart_calc/smart_calc_state.hpp"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>  // Will drag system OpenGL headers

// Main code
int SmartCalc::smartCalc() {
  SmartCalc::CalcState calc_state(1280, 720, "Calculator");

  // Our state
  bool show_calc_window = false;
  bool show_plot_window = false;
  bool show_credit_window = true;
  bool show_deposit_window = true;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  SmartCalc::Calculator calculator_window(&show_calc_window);
  SmartCalc::PlotCalculator plow_window(&show_plot_window);
  SmartCalc::CreditCalculator credit_window(&show_credit_window);
  SmartCalc::DepositCalculator deposit_window(&show_deposit_window);

  // Main loop
  while (!glfwWindowShouldClose(calc_state.window)) {
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (show_calc_window) calculator_window.Draw();
    if (show_plot_window) plow_window.Draw();
    if (show_credit_window) credit_window.Draw();
    if (show_deposit_window) deposit_window.Draw();

    // App windows
    {
      ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
      ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
      ImGui::Begin("Menu");
      ImGui::Checkbox("Calculator", &show_calc_window);
      ImGui::Checkbox("Plot", &show_plot_window);
      ImGui::Checkbox("Credit Calculator", &show_credit_window);
      ImGui::Checkbox("Deposit Calculator", &show_deposit_window);
    }

    ImGui::End();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(calc_state.window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(calc_state.window);
  }

  return 0;
}
