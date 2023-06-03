file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/include/calc_rpn/*.h")

add_library(
    "calc_rpn" STATIC
    calc_deque.c
    tokenize_expression.c
    ${HEADER_LIST}
    # validate.c
    # validate_helpers.c
)

target_include_directories("calc_rpn" PUBLIC ../include)

# target_include_directories(calc_rpn
#     INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
# )
