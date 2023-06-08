find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCHECK REQUIRED check)

add_subdirectory("calc_rpn")
