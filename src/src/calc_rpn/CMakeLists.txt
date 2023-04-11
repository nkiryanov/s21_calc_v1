add_library(
    "calc_rpn" STATIC
    deque.c
    validate.c
    validate_helpers.c
)

target_include_directories(calc_rpn
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
