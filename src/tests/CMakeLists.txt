find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCHECK REQUIRED check)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/tests/*.h")
message("Tests headers list" "${HEADER_LIST}")

add_subdirectory("calc_rpn")
