add_executable(
    "smart_calc.app"
    smart_calc_app.cpp
)

target_link_libraries(
    "smart_calc.app"
    PRIVATE smart_calc
)


install(
    TARGETS "smart_calc.app"
    RUNTIME DESTINATION ./
)
