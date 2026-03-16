/**
 * @file simulation.c
 * @brief Simulation loop and step logic.
 *
 * Handles each simulation step, including random vehicle arrivals,
 * parking, queue management, exit processing and stats updates.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/simulation.h"
#include "../include/parking.h"
#include "../include/config.h"
#include "../include/queue.h"
#include "../include/stats.h"
#include "../include/ui.h"
#include "../include/utils.h"

int rand_arrival(SimConfig *ptr_config){
    if(ptr_config == NULL){
        output(2, "Error: Failed to check arrival. Invalid Arguments.\n", 2, 0, NULL);
        return 0;
    }
    int rand_i = (rand() % 100) + 1;
    if(rand_i <= (int)ptr_config->arrival_probability_percent){
        return 1;
    }
    return 0;
}

int run_simulation(SimConfig *ptr_config, SimStats *ptr_stats){
    if(ptr_config == NULL || ptr_stats == NULL){
        output(2, "Error: Failed to start simulation. Invalid Arguments.\n", 2, 1, ptr_config);
        return -1;
    }

    srand(ptr_config->seed);
    Parking *ptr_parking = init_parking(ptr_config, ptr_stats);
    Queue *ptr_queue = init_queue();
    FILE *ptr_output_file = create_output_file(ptr_config);

    unsigned int total_steps = ptr_config->sim_duration_steps;
    for(unsigned int i = 0; i < total_steps; i++){
        if(rand_arrival(ptr_config) == 1){
            enqueue(ptr_queue, create_vehicle(ptr_stats, ptr_config));
        }

        check_exit(ptr_parking, ptr_stats);

        get_free_spots(ptr_parking, ptr_stats);
        if(ptr_stats->temp_free_spots && ptr_queue->size > 0){
            entry_parking(ptr_parking, dequeue(ptr_queue, ptr_stats), ptr_stats);
        }

        update_simstats(ptr_stats, ptr_parking, ptr_queue);
        update_peak(ptr_stats);
        save_temp_dataset(ptr_stats, ptr_output_file);
        show_running(ptr_stats);
        reset_temp_stats(ptr_stats);
        increment_queue_time(ptr_queue);

        ptr_stats->step_num ++;
    }

    delete_queue(ptr_queue, ptr_stats);
    save_final_dataset(ptr_stats, ptr_output_file);
    close_output_file(ptr_output_file, ptr_config);
    show_results(ptr_stats);
    reset_all_stats(ptr_stats);
    free_parking(ptr_parking);
    free_queue(ptr_queue);

    return 1;
}


/*
PSEUDOCODE

FUNCTION rand_arrival(ptr_config : SimConfig*) RETURNS int
    rand_i = (CALL rand() % 100) + 1
    
    IF rand_i <= ptr_config->arrival_probability_percent DO
        RETURN 1
    ENDIF

    RETURN 0
ENDFUNCTION

FUNCTION run_simulation(ptr_config, ptr_stats)
    CALL srand(ptr_config->seed)
    ptr_parking = CALL init_parking(ptr_config, ptr_stats)
    ptr_queue = CALL init_queue
    ptr_output_file = CALL create_output_file(ptr_config)
    total_steps = ptr_config->sim_duration_steps

    FOR i = 0, i < total_steps, i++ DO
        IF CALL rand_arrival(ptr_config) DO
            CALL enqueue(ptr_queue, CALL create_vehicle(ptr_stats, ptr_config))
        END IF
        
        CALL check_exit(ptr_parking, ptr_stats)

        CALL get_free_spots(ptr_parking, ptr_stats)

        IF ptr_stats->temp_free_spots DO
            CALL entry_parking(ptr_parking, CALL dequeue(ptr_queue, ptr_stats), ptr_stats)
        END IF

        CALL update_simstats(ptr_stats, ptr_parking, ptr_queue)
        CALL update_peak(ptr_stats)
        CALL save_temp_dataset(ptr_stats, ptr_output_file)
        CALL show_running(ptr_stats)
        CALL reset_temp_stats(ptr_stats)
        CALL increment_queue_time(ptr_queue)
        ptr_stats->step_num = ptr_stats->step_num + 1
    END FOR

    // after successfull simulation
    CALL delete_queue(ptr_queue, ptr_stats)
    CALL save_final_dataset(ptr_stats, ptr_output_file)
    CALL close_output_file(ptr_output_file)
    CALL show_results(ptr_stats)
    CALL reset_all_stats(ptr_stats)
    CALL free_parking(ptr_parking)
    CALL free_queue(ptr_queue)

    RETURN 1
    
END FUNCTION
*/