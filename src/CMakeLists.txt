cmake_minimum_required(VERSION 3.22.1)

project("smart_calc" VERSION 0.0.1)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(C_STANDARD 11)
    set(C_STANDARD_REQUIRED True)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()


add_compile_options(-Wall -Werror -Wextra)

add_subdirectory("src")

# add_executable(smart_calc stupid_test.c)
# target_link_libraries(smart_calc calc_rpn)

add_subdirectory("apps")
add_subdirectory("tests")