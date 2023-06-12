file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/include/implot/*.h")

add_library(
    "implot"
    implot.cpp
    implot_items.cpp
    ${HEADER_LIST}
)

target_include_directories(
    "implot"
    PRIVATE ../../include/implot/ ../../include/imgui/
    PUBLIC ../../include/
)

target_link_libraries(
    "implot"
    PUBLIC imgui
)
