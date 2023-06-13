file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/tests/credit_calc/*.h")

add_executable("tests_credit_calc"
    tests_main.c
    master_suite.c
    tests_get_credit_payments.c
    ${HEADER_LIST}
)

target_link_libraries("tests_credit_calc"
    PRIVATE "credit_calc" ${CHECK_LINK_LIBRARIES} pthread
)

target_include_directories(
    "tests_credit_calc"
    PRIVATE ${CHECK_INCLUDE_DIRS}
)

add_test(NAME tests_credit_calc COMMAND tests_credit_calc)
