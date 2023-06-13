cmake_minimum_required(VERSION 3.22.1)

project("smart_calc" VERSION 0.0.1)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED True)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)

    # Set install prefix if this is the main app
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/•install_dir/")

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Add custom cmake utils
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

    # Testing only available if this is the main app and release option = Debug
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(BUILD_TESTING True)

        add_compile_options(--coverage)
        add_link_options(--coverage)

        enable_testing()

        list(APPEND CMAKE_CTEST_ARGUMENTS "--rerun-failed" "--output-on-failure")
    endif(CMAKE_BUILD_TYPE STREQUAL Debug)

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

add_subdirectory("extern")
add_subdirectory("src")
add_subdirectory("apps")

if(BUILD_TESTING)
    add_subdirectory("tests")
endif()
