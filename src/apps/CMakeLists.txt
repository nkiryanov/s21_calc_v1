add_executable(
    "smart_calc_app"
    smart_calc_app.cpp
)

target_link_libraries(
    "smart_calc_app"
    PRIVATE smart_calc
)
