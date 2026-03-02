#include "../include/simulation.h"

/*
PSEUDOCODE

FUNCTION run_simulation
    parking = CALL init_parking
    queue = CALL init_queue
    output_file = CALL create_output_file
    total_steps = config.total_steps

    FOR i = 0, i < total_steps, i++ DO

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