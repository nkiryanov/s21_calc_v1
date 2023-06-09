file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${smart_calc_SOURCE_DIR}/include/SmartCalc/*.h")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH " /opt/homebrew/Cellar/qt/6.5.1/")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable("SmartCalc"
    MANUAL_FINALIZATION
    main.cpp
    smartcalc.cpp
    smartcalc.ui
    ${HEADER_LIST}
)

target_link_libraries("SmartCalc" PRIVATE Qt6::Widgets)

target_include_directories("SmartCalc" PUBLIC ../../include)

set_target_properties("SmartCalc" PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS "SmartCalc"
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable("SmartCalc")
