file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/tests/deposit_calc/*.h")

add_executable("tests_deposit_calc"
    tests_main.c
    master_suite.c
    tests_get_deposit_payments.c
    ${HEADER_LIST}
)

target_link_libraries("tests_deposit_calc"
    PRIVATE "deposit_calc" ${CHECK_LINK_LIBRARIES} pthread
)

target_include_directories(
    "tests_deposit_calc"
    PRIVATE ${CHECK_INCLUDE_DIRS}
)

add_test(NAME tests_deposit_calc COMMAND tests_deposit_calc)
