find_library(CHECK_LIB check REQUIRED)
find_path(CHECK_INCLUDE check.h REQUIRED)

add_executable(calc_tests_exec
    tests_main.c
    master_suite.c
    tests_deque.c
)

target_link_libraries(calc_tests_exec
    PRIVATE calc_rpn ${CHECK_LIB}
)

target_include_directories(
    calc_tests_exec
    PRIVATE ${CHECK_INCLUDE}
)
