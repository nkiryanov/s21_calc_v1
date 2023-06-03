add_executable(
    "manual_test"
    manual_test.c
)

target_link_libraries(
    "manual_test"
    PRIVATE "calc_rpn"
)
