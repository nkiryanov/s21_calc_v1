include(FindCheckLib)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/tests/calc_rpn/*.h")

add_executable("tests_calc_rpn"
    tests_main.c
    master_suite.c
    tests_calc_deque.c
    tests_tokenize_once_function.c
    tests_tokenize_expression.c
    tests_do_shunting_yard.c
    tests_validate_math_expression.c
    tests_evaluate_math.c
    ${HEADER_LIST}
)

target_link_libraries("tests_calc_rpn"
    PRIVATE "calc_rpn" ${CHECK_LINK_LIBRARIES} pthread
)

target_include_directories(
    "tests_calc_rpn"
    PRIVATE ${CHECK_INCLUDE_DIRS}
)

add_test(NAME tests_calc_rpn COMMAND tests_calc_rpn)
