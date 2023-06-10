#ifndef SMART_CALC_SMART_CALC_STATE_H_
#define SMART_CALC_SMART_CALC_STATE_H_

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace SmartCalc {

struct CalcState {
  char glsl_version[100] = "";
  GLFWwindow* window;
  ImGuiIO* io;

  CalcState(int width, int height, const char* title);
  ~CalcState();

  void SetGlfwErrorCallback();
  void SetGlfwWindowHint(char* glsl_version);
  void InitGlfw();
  GLFWwindow* CreateGlfwWindow(int width, int height, const char* title);
  void SetImguiContext();
  ImGuiIO* SetImguiIO();
  void SetImguiStyle();
  void SetRendererBackends(GLFWwindow* window, const char* glsl_version);
};

}  // namespace SmartCalc

#endif  // SMART_CALC_SMART_CALC_STATE_H
