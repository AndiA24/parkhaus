#include "../include/simulation.h"
#include "../include/config.h"
#include "../include/stats.h"

/*
PSEUDOCODE

FUNCTION run_simulation(config, stats)
    parking = CALL init_parking
    queue = CALL init_queue
    output_file = CALL create_output_file
    total_steps = config.total_steps

    FOR i = 0, i < total_steps, i++ DO
        IF CALL rand_arrival((Adress)config) DO
            new_vehicle = CALL create_vehicle
            CALL enqueue(queue, vehicle)
        END IF
        
        CALL check_exits(parking, stats)

        IF CALL get_free_spots DO
            vehicle = CALL dequeue(queue, stats)
            CALL entry_parking(parking, vehicle, stats)
        END IF

        CALL update_simstats
        CALL update_peak
        CALL save_temp_dataset(output_file)
        CALL reset_temp_stats
    END FOR

    // after successfull simulation
    CALL delete_queue(queue)
    CALL free_queue(queue)
    CALL save_final_dataset(output_file)
    CALL close_output_file(output_file)
    CALL reset_all_stats
    CALL free_parking((Adress)parking)
    CALL free_queue((Adress)queue)

END FUNCTION
*/