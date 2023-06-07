file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/include/calc_rpn/*.h")

add_library(
    "calc_rpn" STATIC
    calc_deque.c
    calc_expression.c
    tokenize_expression.c
    shunting_yard.c
    validate_math_expression.c
    evaluate_rpn.c
    ${HEADER_LIST}
)

target_include_directories("calc_rpn" PUBLIC ../../include)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries("calc_rpn" PUBLIC ${MATH_LIBRARY})
endif()
