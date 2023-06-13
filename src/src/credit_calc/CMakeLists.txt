file(GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${smart_calc_SOURCE_DIR}/include/credit_calc/*.h"
)

add_library(
    "credit_calc" STATIC
    credit_calc.c
    ${HEADER_LIST}
)

target_include_directories(
    "credit_calc"
    PUBLIC ../../include/
)

if(MATH_LIBRARY)
    target_link_libraries("credit_calc" PUBLIC ${MATH_LIBRARY})
endif()
