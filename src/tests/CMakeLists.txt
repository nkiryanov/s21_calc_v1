find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCHECK REQUIRED check)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/tests/*.h")
message("Tests headers list" "${HEADER_LIST}")

add_executable("calc_tests_exec"
    tests_main.c
    master_suite.c
    tests_calc_deque.c
    tests_tokenize_once_function.c
    tests_tokenize_expression.c
    tests_do_shunting_yard.c
    tests_validate_math_expression.c
    tests_evaluate_rpn.c
    ${HEADER_LIST}
)

target_link_libraries("calc_tests_exec"
    PRIVATE "calc_rpn" ${LIBCHECK_LINK_LIBRARIES}
)

target_include_directories(
    "calc_tests_exec"
    PRIVATE ${LIBCHECK_INCLUDE_DIRS}
)
