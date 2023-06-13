file(GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${smart_calc_SOURCE_DIR}/include/deposit_calc/*.h"
)

add_library(
    "deposit_calc" STATIC
    deposit_calc.c
    ${HEADER_LIST}
)

target_include_directories(
    "deposit_calc"
    PUBLIC ../../include/
)
