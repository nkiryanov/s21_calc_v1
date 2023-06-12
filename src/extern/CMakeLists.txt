find_package("OpenGL" REQUIRED)
find_package("GLFW" REQUIRED)
include(AddGitSubmodule)

add_git_submodule("imgui" "LICENSE.txt")

set(
  IMGUI_HEADER_LIST
  imgui/imconfig.h
  imgui/imgui_internal.h
  imgui/imgui.h
  imgui/imstb_rectpack.h
  imgui/imstb_textedit.h
  imgui/imstb_truetype.h
  imgui/backends/imgui_impl_glfw.h
  imgui/backends/imgui_impl_opengl3_loader.h
  imgui/backends/imgui_impl_opengl3.h
)

add_library(
    "imgui" STATIC
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_glfw.cpp
    "${IMGUI_HEADER_LIST}"
)

target_include_directories(
    "imgui"
    PUBLIC ./imgui/ ./imgui/backends/ "${GLFW_INCLUDE_DIRS}" "${OPENGL_INCLUDE_DIR}"
)

target_link_libraries(
    "imgui"
    PUBLIC ${GLFW_LINK_LIBRARIES} ${OPENGL_LIBRARIES}
)

add_git_submodule("implot" "README.md")

set(
  IMPLOT_HEADER_LIST
  implot/implot_internal.h
  implot/implot.h
)

add_library(
    "implot" STATIC
    implot/implot_demo.cpp
    implot/implot_items.cpp
    implot/implot.cpp
    "${IMPLOT_HEADER_LIST}"
)

target_include_directories(
    "implot"
    PRIVATE ./implot/ ./imgui/
    PUBLIC ./implot
)

target_link_libraries(
    "implot"
    PUBLIC imgui
)
