cmake_minimum_required(VERSION 3.26.1)

project("smart_calc" VERSION 0.0.1)

set(C_STANDARD 11)
set(C_STANDARD_REQUIRED True)

add_compile_options(-Wall -Werror -Wextra)

add_subdirectory("calc_rpn")

add_executable(smart_calc stupid_test.c)
target_link_libraries(smart_calc calc_rpn)

add_subdirectory("tests")
