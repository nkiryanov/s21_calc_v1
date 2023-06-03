find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCHECK REQUIRED check)

add_executable(calc_tests_exec
    tests_main.c
    master_suite.c
    tests_calc_deque.c
    tests_tokenize_expression.c
    # tests_validate.c
)

target_link_libraries(calc_tests_exec
    PRIVATE calc_rpn ${LIBCHECK_LINK_LIBRARIES}
)

target_include_directories(
    calc_tests_exec
    PRIVATE ${LIBCHECK_INCLUDE_DIRS}
)
