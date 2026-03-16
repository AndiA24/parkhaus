cmake_minimum_required(VERSION 3.10)
project(Parkhaus C)

add_executable(parkhaus
    src/main.c
    src/ui.c
    src/config.c
    src/stats.c
    src/utils.c
    src/parking.c
    src/queue.c
    src/simulation.c
    src/vehicle.c
)

target_include_directories(parkhaus PRIVATE include)

if(WIN32)
    target_include_directories(parkhaus PRIVATE pdcurses)
    target_link_libraries(parkhaus PRIVATE ${CMAKE_SOURCE_DIR}/pdcurses/wincon/libpdcurses.a winmm)
else()
    target_link_libraries(parkhaus PRIVATE ncurses)
endif()

option(UNIT_TEST "Build without UI for unit testing" OFF)
if(UNIT_TEST)
    target_compile_definitions(parkhaus PRIVATE UNIT_TEST)
endif()