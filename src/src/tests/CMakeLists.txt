find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

add_executable(calc_tests_exec
    tests_main.c
    master_suite.c
    tests_deque.c
)

target_link_libraries(calc_tests_exec
    PRIVATE calc_rpn ${CHECK_LINK_LIBRARIES}
)

target_include_directories(
    calc_tests_exec
    PRIVATE ${CHECK_INCLUDE_DIRS}
)
