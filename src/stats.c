#include "../include/stats.h"
#include "../include/queue.h"
#include "../include/config.h"
/*
PSEUDOCODE

FUNCTION init_simstats()
    
    Allocate Memory for SimStats Function wrte adress in ptr_simstats

    IF ptr_simstats == NULL (memory allocation failed)
        OUTPUT Memory Allocation Filed
        return NULL
    END IF

    set all field to 0 
    return ptr_simstats
END FUNCTION

FUNCTION create_output_file(ptr_config : SimConfig*) RETURNS FILE*
    user_input : char
    ptr_output_file : FILE*

    DO
        ptr_output_file = fopen(ptr_config->output_file_name, "r")

        IF ptr_output_file != NULL
            fclose(ptr_output_file)
            CALL printf("File already exists. Overwrite? (y/n): ")
            CALL scanf(" %c", &user_input)

            IF user_input == 'y'
                BREAK
            ELSE
                CALL printf("Enter new file name: ")
                CALL scanf("%s", ptr_config->output_file_name) 
            ENDIF
        ELSE
            BREAK
        ENDIF
    WHILE TRUE

    ptr_output_file = fopen(ptr_config->output_file_name, "w")

    IF ptr_output_file == NULL
        RETURN NULL
    ENDIF

    // Write configuration values
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->num_decks)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->spots_per_deck)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->initial_occupancy)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->max_parking_duration_steps)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->min_parking_duration_steps)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->sim_duration_steps)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->arrival_probability_percent)
    CALL fprintf(ptr_output_file, "%s\n", ptr_config->output_file_name)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->seed)

    RETURN ptr_output_file
END FUNCTION


FUNCTION update_simstats(SimStats (Adress)ptr_stats, Parking (Adress)ptr_parking, Queue (Adress)ptr_queue)
    
    // calculate rel occupancy
    IF ptr_parking->total_capacity > 0 THEN
        ptr_stats->temp_rel_occupancy_percent = ((float)ptr_parking->occupied_count / (float)ptr_parking->total_capacity) * 100
    ELSE
        ptr_parking->total_capacity = 0
    ENDIF

    IF ptr_stats->temp_rel_occupancy_percent == 100 THEN
        ptr_stats->time_full_occupancy = ptr_stats->time_full_occupancy + 1
    END IF

    // update queue length
    ptr_stats->temp_queue_length = ptr_queue->size

END FUNCTION


FUNCTION update_peak((Adress)ptr_simstats)
    IF ptr_simstats->temp_rel_occupancy_percent > ptr_simstats->peak_rel_occupancy THEN // check whether current occupancy is higher then saved peak
        ptr_simstats->peak_rel_occupancy = ptr_simstats->temp_rel_occupancy_percent
        ptr_simstats->step_highest_occupancy = ptr_simstats->step_num
    END IF
    IF ptr_simstats->temp_queue_length > ptr_simstats->peak_queue_length THEN // check wheather current queue length is higher than saved peak
        ptr_simstats->peak_queue_length = ptr_simstats->temp_queue_length
        ptr_simstats->step_longest_queue = ptr_simstats->step_num
    END IF
END FUNCTION


FUNCTION save_temp_dataset(ptr_simstats : SimStats*, ptr_output_file : FILE*)
    
    IF ptr_output_file == NULL
        RETURN
    ENDIF

    CALL printf("%u\n", ptr_config->temp_exits)
    CALL printf("%u\n", ptr_config->temp_entrys)
    CALL printf("%f\n", ptr_config->temp_rel_occupancy_percent)
    CALL printf("%u\n", ptr_config->temp_queue_length)
    CALL printf("%u\n", ptr_config->temp_free_spots)
    CALL printf("%u\n", ptr_config->temp_time_left)
    
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->temp_exits)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->temp_entrys)
    CALL fprintf(ptr_output_file, "%f\n", ptr_config->temp_rel_occupancy_percent)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->temp_queue_length)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->temp_free_spots)
    CALL fprintf(ptr_output_file, "%u\n", ptr_config->temp_time_left)

END FUNCTION


FUNCTION reset_temp_stats(SimStats (Adress)ptr_stats)
    ptr_stats->temp_exits = 0
    ptr_stats->temp_entrys = 0
    ptr_stats->temp_rel_occupancy_percent = 0
    ptr_stats->temp_queue_length = 0
    ptr_stats->temp_free_spots = 0
    ptr_stats->temp_time_left = 0
END FUNCTION


FUNCTION save_final_dataset()

END FUNCTION


FUNCTION close_output_file(FILE ptr_output_file)
    Close file (ptr_output_file)
END FUNCTION


FUNCTION reset_all_stats
    ptr_stats->step_num = 0
    ptr_stats->temp_exits = 0
    ptr_stats->temp_entrys = 0
    ptr_stats->temp_rel_occupancy_percent = 0
    ptr_stats->temp_queue_length = 0
    ptr_stats->total_exits = 0
    ptr_stats->total_entrys = 0
    ptr_stats->total_queued = 0
    ptr_stats->total_queue_time = 0
    ptr_stats->total_parking_time = 0
    ptr_stats->time_full_occupancy = 0
    ptr_stats->peak_queue_length = 0
    ptr_stats->step_longest_queue = 0
    ptr_stats->peak_rel_occupancy = 0
    ptr_stats->step_highest_occupancy = 0
END FUNCTION


FUNCTION free_stats(SimStats (Adress)ptr_stats)
    Free memory allocated for (ptr_stats)
END FUNCTION


END PSEUDOCODE
*/