cmake_minimum_required(VERSION 3.10)
project(Parkhaus C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

# Hauptprogramm
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
    target_link_libraries(parkhaus PRIVATE ncurses m)
endif()

# Tests
enable_testing()

if(NOT WIN32)
    link_libraries(m)
endif()

add_executable(test_init_occ test/test_parking_init_occ.c src/parking.c src/config.c src/stats.c src/vehicle.c src/utils.c)
target_include_directories(test_init_occ PRIVATE include)
target_compile_definitions(test_init_occ PRIVATE UNIT_TEST)
add_test(NAME test_init_occ COMMAND test_init_occ)

add_executable(test_init_parking test/test_parking_init_parking.c src/parking.c src/stats.c src/config.c src/vehicle.c src/utils.c)
target_include_directories(test_init_parking PRIVATE include)
target_compile_definitions(test_init_parking PRIVATE UNIT_TEST)
add_test(NAME test_init_parking COMMAND test_init_parking)

add_executable(test_init_stats test/test_stats_init_stats.c src/stats.c src/config.c src/parking.c src/vehicle.c src/utils.c)
target_include_directories(test_init_stats PRIVATE include)
target_compile_definitions(test_init_stats PRIVATE UNIT_TEST)
add_test(NAME test_init_stats COMMAND test_init_stats)

add_executable(test_update_stats test/test_stats_update_stats.c src/stats.c src/vehicle.c src/config.c src/utils.c)
target_include_directories(test_update_stats PRIVATE include)
target_compile_definitions(test_update_stats PRIVATE UNIT_TEST)
add_test(NAME test_update_stats COMMAND test_update_stats)

add_executable(test_update_peak test/test_stats_update_peak.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_update_peak PRIVATE include)
target_compile_definitions(test_update_peak PRIVATE UNIT_TEST)
add_test(NAME test_update_peak COMMAND test_update_peak)

add_executable(test_reset_temp_stats test/test_stats_reset_temp_stats.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_reset_temp_stats PRIVATE include)
target_compile_definitions(test_reset_temp_stats PRIVATE UNIT_TEST)
add_test(NAME test_reset_temp_stats COMMAND test_reset_temp_stats)

add_executable(test_reset_all_stats test/test_stats_reset_all_stats.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_reset_all_stats PRIVATE include)
target_compile_definitions(test_reset_all_stats PRIVATE UNIT_TEST)
add_test(NAME test_reset_all_stats COMMAND test_reset_all_stats)

add_executable(test_free_stats test/test_stats_free_stats.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_free_stats PRIVATE include)
target_compile_definitions(test_free_stats PRIVATE UNIT_TEST)
add_test(NAME test_free_stats COMMAND test_free_stats)

add_executable(test_free_parking test/test_parking_free_parking.c src/parking.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_free_parking PRIVATE include)
target_compile_definitions(test_free_parking PRIVATE UNIT_TEST)
add_test(NAME test_free_parking COMMAND test_free_parking)

add_executable(test_rand_arrival test/test_simulation_rand_arrival.c src/config.c src/simulation.c src/parking.c src/stats.c src/queue.c src/vehicle.c src/utils.c)
target_include_directories(test_rand_arrival PRIVATE include)
target_compile_definitions(test_rand_arrival PRIVATE UNIT_TEST)
add_test(NAME test_rand_arrival COMMAND test_rand_arrival)

add_executable(test_create_vehicle test/test_vehicle_create_vehicle.c src/config.c src/parking.c src/stats.c src/vehicle.c src/utils.c)
target_include_directories(test_create_vehicle PRIVATE include)
target_compile_definitions(test_create_vehicle PRIVATE UNIT_TEST)
add_test(NAME test_create_vehicle COMMAND test_create_vehicle)

add_executable(test_free_vehicle test/test_vehicle_free_vehicle.c src/vehicle.c src/config.c src/utils.c)
target_include_directories(test_free_vehicle PRIVATE include)
target_compile_definitions(test_free_vehicle PRIVATE UNIT_TEST)
add_test(NAME test_free_vehicle COMMAND test_free_vehicle)

add_executable(test_parking_entry_parking test/test_parking_entry_parking.c src/parking.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_parking_entry_parking PRIVATE include)
target_compile_definitions(test_parking_entry_parking PRIVATE UNIT_TEST)
add_test(NAME test_parking_entry_parking COMMAND test_parking_entry_parking)

add_executable(test_check_exits test/test_parking_check_exits.c src/parking.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_check_exits PRIVATE include)
target_compile_definitions(test_check_exits PRIVATE UNIT_TEST)
add_test(NAME test_check_exits COMMAND test_check_exits)

add_executable(test_get_free_spots test/test_parking_get_free_spots.c src/parking.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_get_free_spots PRIVATE include)
target_compile_definitions(test_get_free_spots PRIVATE UNIT_TEST)
add_test(NAME test_get_free_spots COMMAND test_get_free_spots)

add_executable(test_close_output_file test/test_stats_close_output_file.c src/parking.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_close_output_file PRIVATE include)
target_compile_definitions(test_close_output_file PRIVATE UNIT_TEST)
add_test(NAME test_close_output_file COMMAND test_close_output_file)

add_executable(test_create_output_file test/test_stats_create_output_file.c src/parking.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_create_output_file PRIVATE include)
target_compile_definitions(test_create_output_file PRIVATE UNIT_TEST)
add_test(NAME test_create_output_file COMMAND test_create_output_file)

add_executable(test_save_final_dataset test/test_stats_save_final_dataset.c src/parking.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_save_final_dataset PRIVATE include)
target_compile_definitions(test_save_final_dataset PRIVATE UNIT_TEST)
add_test(NAME test_save_final_dataset COMMAND test_save_final_dataset)

add_executable(test_save_temp_dataset test/test_stats_save_temp_dataset.c src/parking.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_save_temp_dataset PRIVATE include)
target_compile_definitions(test_save_temp_dataset PRIVATE UNIT_TEST)
add_test(NAME test_save_temp_dataset COMMAND test_save_temp_dataset)

add_executable(test_simulation_run_simulation test/test_simulation_run_simulation.c src/simulation.c src/config.c src/parking.c src/stats.c src/queue.c src/vehicle.c src/utils.c)
target_include_directories(test_simulation_run_simulation PRIVATE include)
target_compile_definitions(test_simulation_run_simulation PRIVATE UNIT_TEST)
add_test(NAME test_simulation_run_simulation COMMAND test_simulation_run_simulation)

add_executable(test_queue_init_queue test/test_queue_init_queue.c src/queue.c src/vehicle.c src/config.c src/utils.c)
target_include_directories(test_queue_init_queue PRIVATE include)
target_compile_definitions(test_queue_init_queue PRIVATE UNIT_TEST)
add_test(NAME test_queue_init_queue COMMAND test_queue_init_queue)

add_executable(test_queue_free_queue test/test_queue_free_queue.c src/queue.c src/vehicle.c src/config.c src/utils.c)
target_include_directories(test_queue_free_queue PRIVATE include)
target_compile_definitions(test_queue_free_queue PRIVATE UNIT_TEST)
add_test(NAME test_queue_free_queue COMMAND test_queue_free_queue)

add_executable(test_queue_delete_queue test/test_queue_delete_queue.c src/queue.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_queue_delete_queue PRIVATE include)
target_compile_definitions(test_queue_delete_queue PRIVATE UNIT_TEST)
add_test(NAME test_queue_delete_queue COMMAND test_queue_delete_queue)

add_executable(test_queue_enqueue test/test_queue_enqueue.c src/queue.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_queue_enqueue PRIVATE include)
target_compile_definitions(test_queue_enqueue PRIVATE UNIT_TEST)
add_test(NAME test_queue_enqueue COMMAND test_queue_enqueue)

add_executable(test_queue_dequeue test/test_queue_dequeue.c src/queue.c src/vehicle.c src/stats.c src/config.c src/utils.c)
target_include_directories(test_queue_dequeue PRIVATE include)
target_compile_definitions(test_queue_dequeue PRIVATE UNIT_TEST)
add_test(NAME test_queue_dequeue COMMAND test_queue_dequeue)

add_executable(test_config_create_config test/test_config_create_config.c src/config.c src/utils.c)
target_include_directories(test_config_create_config PRIVATE include)
target_compile_definitions(test_config_create_config PRIVATE UNIT_TEST)
add_test(NAME test_config_create_config COMMAND test_config_create_config)

add_executable(test_config_populate_with_defaults test/test_config_populate_with_defaults.c src/config.c src/utils.c)
target_include_directories(test_config_populate_with_defaults PRIVATE include)
target_compile_definitions(test_config_populate_with_defaults PRIVATE UNIT_TEST)
add_test(NAME test_config_populate_with_defaults COMMAND test_config_populate_with_defaults)

add_executable(test_config_get_config test/test_config_get_config.c src/config.c src/utils.c)
target_include_directories(test_config_get_config PRIVATE include)
target_compile_definitions(test_config_get_config PRIVATE UNIT_TEST)
add_test(NAME test_config_get_config COMMAND test_config_get_config)

add_executable(test_config_save_config test/test_config_save_config.c src/config.c src/utils.c)
target_include_directories(test_config_save_config PRIVATE include)
target_compile_definitions(test_config_save_config PRIVATE UNIT_TEST)
add_test(NAME test_config_save_config COMMAND test_config_save_config)

add_executable(test_config_free_config test/test_config_free_config.c src/config.c src/utils.c)
target_include_directories(test_config_free_config PRIVATE include)
target_compile_definitions(test_config_free_config PRIVATE UNIT_TEST)
add_test(NAME test_config_free_config COMMAND test_config_free_config)

# add_executable(test_run_simulation test/test_simulation_run_simulation.c src/simulation.c src/config.c src/parking.c src/stats.c src/queue.c src/vehicle.c src/utils.c)
# target_include_directories(test_run_simulation PRIVATE include)
# target_compile_definitions(test_run_simulation PRIVATE UNIT_TEST)
# add_test(NAME test_run_simulation COMMAND test_run_simulation)
