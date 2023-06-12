cmake_minimum_required(VERSION 3.22.1)

project("smart_calc" VERSION 0.0.1)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED True)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Add custom cmake utils
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    enable_testing()
    set(BUILD_TESTING True)
    list(APPEND CMAKE_CTEST_ARGUMENTS "--rerun-failed" "--output-on-failure")

    # Set app wide compiller options
    add_compile_options(-Wall -Werror -Wextra)

    # Docs only available if this is the main app
    find_package(Doxygen)

    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

add_subdirectory("src/calc_rpn")
add_subdirectory("src/imgui")
add_subdirectory("src/implot")
add_subdirectory("src/smart_calc")
add_subdirectory("apps")


# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory("tests/calc_rpn")
endif()
