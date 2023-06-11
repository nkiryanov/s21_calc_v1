#include "smart_calc/smart_calc_state.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace SmartCalc;

static void CalcErrorCallback(int error, const char* description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void CalcState::SetGlfwWindowHint(char* glsl_version) {
// Actually don't know why different systems has different settings.
// The code was carefully copy-pasted from
// https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl3/main.cpp

// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char* version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

#elif defined(__APPLE__)
  // GL 3.2 + GLSL 150
  const char* version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char* version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

  strcpy(glsl_version, version);
}

void CalcState::SetGlfwErrorCallback() {
  glfwSetErrorCallback(CalcErrorCallback);
}

void CalcState::InitGlfw() {
  if (glfwInit() == GLFW_FALSE) {
    fprintf(stderr, "Can't initialize GLFW instance");
    std::exit(EXIT_FAILURE);
  }
}

GLFWwindow* CalcState::CreateGlfwWindow(int width, int height,
                                       const char* title) {
  // Create window with graphics context
  GLFWwindow* window = nullptr;
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (window == nullptr) {
    fprintf(stderr, "Can't create GLFW window.");
    std::exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);  // Enable vsync

  return window;
}

void CalcState::SetImguiContext() {
  // Setup Dear ImGui context

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
}

ImGuiIO* CalcState::SetImguiIO() {
  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  return &io;
}

void CalcState::SetImguiStyle() {
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
}

void CalcState::SetRendererBackends(GLFWwindow* window,
                                    const char* glsl_version) {
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

CalcState::CalcState(int width, int height, const char* title) {
  CalcState::SetGlfwErrorCallback();
  CalcState::InitGlfw();
  CalcState::SetGlfwWindowHint(static_cast<char*>(glsl_version));

  window = CalcState::CreateGlfwWindow(width, height, title);

  CalcState::SetImguiContext();
  io = CalcState::SetImguiIO();

  CalcState::SetImguiStyle();
  CalcState::SetRendererBackends(window, static_cast<const char*>(glsl_version));
}


CalcState::~CalcState() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
}
