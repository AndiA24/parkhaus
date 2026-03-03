#include "../include/simulation.h"
#include "../include/config.h"
#include "../include/stats.h"

/*
PSEUDOCODE

/*
FUNCTION rand_arrival(ptr_config : SimConfig*) RETURNS int
    rand_i = (CALL rand() % 100) + 1
    
    IF rand_i <= ptr_config->arrival_probability_percent DO
        RETURN 1
    ENDIF

    RETURN 0
ENDFUNCTION

FUNCTION run_simulation(ptr_config, ptr_stats)
    ptr_parking = CALL init_parking(ptr_config, ptr_stats)
    ptr_queue = CALL init_queue
    ptr_output_file = CALL create_output_file
    total_steps = ptr_config->sim_duration_steps
    CALL srand(ptr_config->seed)

    FOR i = 0, i < total_steps, i++ DO
        IF CALL rand_arrival(ptr_config) DO
            CALL enqueue(ptr_queue, CALL create_vehicle(ptr_stats, ptr_config))
        END IF
        
        CALL check_exit(ptr_parking, ptr_stats)

        IF CALL get_free_spots(ptr_parking) DO
            CALL entry_parking(ptr_parking, CALL dequeue(ptr_queue, ptr_stats), ptr_stats)
        END IF

        CALL update_simstats(ptr_stats, ptr_parking, ptr_queue)
        CALL update_peak(ptr_stats)
        CALL save_temp_dataset(ptr_stats, ptr_output_file)
        CALL show_running(ptr_stats)
        CALL reset_temp_stats(ptr_stats)
        CALL increment_queue_time
        ptr_stats->step_num = ptr_stats->step_num + 1
    END FOR

    // after successfull simulation
    CALL delete_queue(ptr_queue, ptr_stats)
    CALL save_final_dataset(ptr_stats, ptr_output_file)
    CALL close_output_file(output_file)
    CALL reset_all_stats
    CALL free_parking(ptr_parking)
    CALL free_queue(ptr_queue)
    CALL show_results(ptr_stats)

END FUNCTION
*/