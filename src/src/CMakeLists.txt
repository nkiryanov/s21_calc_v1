file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/include/calc_rpn/*.h")

add_library(
    "calc_rpn" STATIC
    calc_deque.c
    tokenize_expression.c
    calc_shunting_yard.c
    ${HEADER_LIST}
    # validate.c
    # validate_helpers.c
)

target_include_directories("calc_rpn" PUBLIC ../include)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries("calc_rpn" PUBLIC ${MATH_LIBRARY})
endif()
