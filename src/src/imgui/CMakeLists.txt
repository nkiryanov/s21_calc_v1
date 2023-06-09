file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/include/imgui/*.h")

find_package("OpenGL" REQUIRED)
find_package("GLFW" REQUIRED)

add_library(
    "imgui"
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
    backends/imgui_impl_opengl3.cpp
    backends/imgui_impl_glfw.cpp
    ${HEADER_LIST}
)

target_include_directories(
    "imgui"
    PRIVATE ../../include/imgui/
    PUBLIC ../../include/ ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(
    "imgui"
    PUBLIC ${GLFW_LINK_LIBRARIES} ${OPENGL_LIBRARIES}
)
