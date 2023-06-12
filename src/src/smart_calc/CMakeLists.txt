file(GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${smart_calc_SOURCE_DIR}/include/smart_calc/*.hpp"
    "${smart_calc_SOURCE_DIR}/include/smart_calc/*.h"
)

add_library(
    "smart_calc" STATIC
    smart_calc.cpp
    smart_calc_state.cpp
    base_calculator.cpp
    calculator.cpp
    plot_calculator.cpp
    ${HEADER_LIST}
)

target_include_directories(
    "smart_calc"
    PUBLIC ../../include/
)

target_link_libraries(
    "smart_calc"
    PRIVATE "imgui" "implot" "calc_rpn"
)
