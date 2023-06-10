find_package("PkgConfig")

pkg_check_modules(GLFW glfw3)

message("!!! GLFW_FOUND ="  "${GLFW_FOUND}")

# Look for GLFW include dir and libraries
if(NOT GLFW_FOUND)
    if (GLFW_REQUIRED)
        message(FATAL_ERROR "Graphic Library Framework was not found, please install `glfw3` lib")
    endif(GLFW_REQUIRED)
endif(NOT GLFW_FOUND)
