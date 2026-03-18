/**
 * @file stats.c
 * @brief Simulation statistics collection, processing and output.
 *
 * Provides functions to initialise, update, print, save and free the
 * statistics collected during the parking simulation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/stats.h"
#include "../include/parking.h"
#include "../include/queue.h"
#include "../include/config.h"
#include "../include/utils.h"

#define TEMP_STRING_SIZE        80
#define PERCENT_PRECISION_SCALE 10000.0f
#define PERCENT_MAX             100.0f


SimStats *init_simstats() {
    SimStats *ptr_stats = calloc(1,sizeof(*ptr_stats));
    if (ptr_stats == NULL) {
        output(2, "Error: Failed to allocate memory for the Stats Struct.\n", 2, 0, NULL);
        return NULL;
    }
    return ptr_stats;
}


FILE *create_output_file(SimConfig *ptr_config)
{
    // validate input pointer
    if (ptr_config == NULL) {
        return NULL;
    }

    FILE *ptr_output_file = NULL;

    // open file for writing (silently overwrite if it already exists)
    char temp_string[TEMP_STRING_SIZE];
    snprintf(temp_string, sizeof(temp_string), "%s.csv", ptr_config->output_file_name); //always add .csv to end of a filename
    ptr_output_file = fopen(temp_string, "w");
    if (ptr_output_file == NULL) {
        return NULL;
    }

    // write simulation config as a self-documenting header at the top of the CSV
    fprintf(ptr_output_file,
        "num_decks,spots_per_deck,initial_occupancy,max_parking_duration_steps,"
        "min_parking_duration_steps,sim_duration_steps,arrival_probability_percent,"
        "output_file_name,seed\n");

    // write the config values
    fprintf(ptr_output_file, "%u,%u,%u,%u,%u,%u,%u,%s,%u\n",
        ptr_config->num_decks,
        ptr_config->spots_per_deck,
        ptr_config->initial_occupancy,
        ptr_config->max_parking_duration_steps,
        ptr_config->min_parking_duration_steps,
        ptr_config->sim_duration_steps,
        ptr_config->arrival_probability_percent,
        ptr_config->output_file_name,
        ptr_config->seed);

    // write column headers for per-step statistics
    fprintf(ptr_output_file, "step_num,temp_exits,temp_entries,temp_rel_occupancy_percent,"
    "temp_queue_length,temp_free_spots,temp_time_left\n");
    
    return ptr_output_file;
}


int update_simstats(SimStats *ptr_stats, Parking *ptr_parking, Queue *ptr_queue) {
    if (ptr_stats == NULL || ptr_parking == NULL || ptr_queue == NULL) {
        output(2, "Error: Failed to update Stats. Invalid argument.\n", 2, 0, NULL);
        return -1;
    }

    // calculate relative occupancy for current step
    if (ptr_parking->total_capacity > 0) {
        // multiply with 1000 and floor to round down to two decimals
        ptr_stats->temp_rel_occupancy_percent = floor(((float)ptr_parking->occupied_count / (float)ptr_parking->total_capacity) * PERCENT_PRECISION_SCALE) / PERCENT_MAX;
    }
    else{
        ptr_stats->temp_rel_occupancy_percent = 0;
    }

    // save current queue-length
    ptr_stats->temp_queue_length = ptr_queue->size;

    // calculate avg relative occupancy using running avg formular
    ptr_stats->avg_rel_occupancy += (ptr_stats->temp_rel_occupancy_percent - ptr_stats->avg_rel_occupancy) / (ptr_stats->step_num + 1);

    // save free spots for this step
    ptr_stats->temp_free_spots = ptr_parking->total_capacity - ptr_parking->occupied_count;

    // if parking is full increment counter for full steps
    if (ptr_parking->occupied_count == ptr_parking->total_capacity) {
        ptr_stats->time_full_occupancy ++;
    }

    // each parked vehicle is one step closer to exit, so subtract 1 from the average
    if (ptr_parking->occupied_count > 0) {
        ptr_stats->temp_time_left -= 1.0;
    }
    else{
        ptr_stats->temp_time_left = 0;
    }

    return 0;
}


int update_peak(SimStats *ptr_stats) {
    if (ptr_stats == NULL) {
        output(2, "Error: Failed to update peak-values. Invalid arguments.\n", 2, 0, NULL);
        return -1;
    }

    // check if current values are higher then saved peaks
    if (ptr_stats->temp_rel_occupancy_percent > ptr_stats->peak_rel_occupancy) {
        ptr_stats->peak_rel_occupancy = ptr_stats->temp_rel_occupancy_percent;
        ptr_stats->step_highest_occupancy = ptr_stats->step_num;
    }
    if (ptr_stats->temp_queue_length > ptr_stats->peak_queue_length) {
        ptr_stats->peak_queue_length = ptr_stats->temp_queue_length;
        ptr_stats->step_longest_queue = ptr_stats->step_num;
    }
    return 0;
}


int save_temp_dataset(SimStats *ptr_stats, FILE *ptr_output_file) {
    // valdate input pointers
    if (ptr_stats == NULL || ptr_output_file == NULL) {
        output(2, "Error: Failed to save temp dataset. Invalid Argument.\n", 2, 0, NULL);
        return -1;
    }

    // write per-step statistics 
    fprintf(ptr_output_file,
        "%u,%u,%u,%.2f,%u,%u,%f\n",
        ptr_stats->step_num,
        ptr_stats->temp_exits,
        ptr_stats->temp_entries,
        ptr_stats->temp_rel_occupancy_percent,
        ptr_stats->temp_queue_length,
        ptr_stats->temp_free_spots,
        ptr_stats->temp_time_left);

    return 1;
}


int reset_temp_stats(SimStats *ptr_stats) {
    if (ptr_stats == NULL) {
        output(2, "Error: Failed to reset temp Stats. Invalid Argument.\n", 2, 0, NULL);
        return -1;
    }
    ptr_stats->temp_entries = 0;
    ptr_stats->temp_exits = 0;
    ptr_stats->temp_free_spots = 0;
    ptr_stats->temp_queue_length = 0;
    ptr_stats->temp_rel_occupancy_percent = 0;

    return 0;
}


int save_final_dataset(SimStats *ptr_stats, FILE *ptr_output_file) {
    // valdate input pointers
    if (ptr_stats == NULL || ptr_output_file == NULL) {
        output(2, "Error: Failed to save final dataset. Invalid argumant\n", 2, 0, NULL);
        return -1;
    }

    // write column headers for final statistics
    fprintf(ptr_output_file, "total_exits,total_entries,total_queued,total_queue_time,"
    "total_parking_time,time_full_occupancy,peak_queue_length,step_longest_queue,"
    "peak_rel_occupancy,step_highest_occupancy\n");

    // write final statistics
    fprintf(ptr_output_file,
        "%u,%u,%u,%llu,%llu,%u,%u,%u,%.2f,%u\n",
        ptr_stats->total_exits,
        ptr_stats->total_entries,
        ptr_stats->total_queued,
        (unsigned long long)ptr_stats->total_queue_time,    //cast to long long to avoid warnings during compilation on Linux
        (unsigned long long)ptr_stats->total_parking_time,  //cast to long long to avoid warnings during compilation on Linux
        ptr_stats->time_full_occupancy,
        ptr_stats->peak_queue_length,
        ptr_stats->step_longest_queue,
        ptr_stats->peak_rel_occupancy,
        ptr_stats->step_highest_occupancy);

    return 1;
}


int close_output_file(FILE *ptr_output_file) {
    if (ptr_output_file == NULL) {
        printf("Error: Failed to close output file. Invalid Argument.\n");
        return -1;
    }
    if (fclose(ptr_output_file) == EOF) {
        output(2, "Error: Failed to close output file.\n", 2, 0, NULL);
        return -1;
    }
    return 0;
}


int reset_all_stats(SimStats *ptr_stats) {
    if (ptr_stats == NULL) {
        output(2, "Error: Failed to reset Stats. Invalid Argument.\n", 2, 0, NULL);
        return -1;
    }
    ptr_stats->step_num = 0;
    ptr_stats->id_count = 0;
    ptr_stats->temp_exits = 0;
    ptr_stats->temp_entries = 0;
    ptr_stats->temp_rel_occupancy_percent = 0;
    ptr_stats->temp_queue_length = 0;
    ptr_stats->temp_free_spots = 0;
    ptr_stats->temp_time_left = 0;
    ptr_stats->total_exits = 0;
    ptr_stats->total_entries = 0;
    ptr_stats->total_queued = 0;
    ptr_stats->total_queue_time = 0;
    ptr_stats->total_parking_time = 0;
    ptr_stats->time_full_occupancy = 0;
    ptr_stats->avg_rel_occupancy = 0;
    ptr_stats->peak_queue_length = 0;
    ptr_stats->step_longest_queue = 0;
    ptr_stats->peak_rel_occupancy = 0;
    ptr_stats->step_highest_occupancy = 0;

    return 0;
}


int free_stats(SimStats *ptr_stats) {
    if (ptr_stats == NULL) {
        output(2, "Error: Failed to free memory allocated for Stats. Invalid Argument\n", 2, 0, NULL);
        return -1;
    }
    free(ptr_stats);
    return 0;
}

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
                ptr_output_file = fopen(ptr_config->output_file_name, "w")
                IF ptr_output_file == NULL
                    RETURN NULL
                ENDIF
                    CALL fclose(ptr_output_file)
                BREAK
            ELSE
                CALL printf("Enter new file name: ")
                CALL scanf("%69s", ptr_config->output_file_name)
            ENDIF
        ELSE
            BREAK
        ENDIF
    WHILE TRUE

    ptr_output_file = CALL fopen(ptr_config->output_file_name, "a")

    IF ptr_output_file == NULL
        RETURN NULL
    ENDIF

    // Write configuration values
    CALL fprintf(ptr_output_file, "%u,%u,%u,%u,%u,%u,%u,%s,%u\n", 
        ptr_config->num_decks, 
        ptr_config->spots_per_deck, 
        ptr_config->initial_occupancy, 
        ptr_config->max_parking_duration_steps, 
        ptr_config->min_parking_duration_steps, 
        ptr_config->sim_duration_steps, 
        ptr_config->arrival_probability_percent, 
        ptr_config->output_file_name, 
        ptr_config->seed)

    CALL fprintf(ptr_output_file,
        "exits,entries,rel_occupancy,queue_length,free_spots,time_left\n")

    RETURN ptr_output_file
END FUNCTION


FUNCTION update_simstats(SimStats (Adress)ptr_simstats, Parking (Adress)ptr_parking, Queue (Adress)ptr_queue)
    IF !ptr_simstats OR !ptr_parking OR !ptr_queue THEN
        RETURN
    ENDIF

    // calculate rel occupancy
    IF ptr_parking->total_capacity > 0 THEN
        ptr_simstats->temp_rel_occupancy_percent = ((float)ptr_parking->occupied_count / (float)ptr_parking->total_capacity) * 100
    ELSE
        ptr_simstats->temp_rel_occupancy_percent = 0
    ENDIF

    // running average formular to add the rel. occupancy of the step to the avg.
    ptr_simstats->avg_rel_occupancy =
    (ptr_simstats->avg_rel_occupancy * ptr_simstats->step_num
     + ptr_simstats->temp_rel_occupancy_percent)
    / (ptr_simstats->step_num + 1)

    IF ptr_parking->occupied_count == ptr_parking->total_capacity THEN
        ptr_simstats->time_full_occupancy = ptr_simstats->time_full_occupancy + 1
    END IF

    IF ptr_parking->occupied_count > 0 THEN
        ptr_simstats->temp_time_left = ptr_simstats->temp_time_left / ptr_parking->occupied_count
    END IF
    // update queue length
    ptr_simstats->temp_queue_length = ptr_queue->size

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

    CALL fprintf(ptr_output_file,
        "%u,%u,%.2f,%u,%u,%u\n",
        ptr_simstats->temp_exits,
        ptr_simstats->temp_entries,
        ptr_simstats->temp_rel_occupancy_percent,
        ptr_simstats->temp_queue_length,
        ptr_simstats->temp_free_spots,
        ptr_simstats->temp_time_left)

END FUNCTION


FUNCTION reset_temp_stats(SimStats (Adress)ptr_simstats)
    ptr_simstats->temp_exits = 0
    ptr_simstats->temp_entries = 0
    ptr_simstats->temp_rel_occupancy_percent = 0
    ptr_simstats->temp_queue_length = 0
    ptr_simstats->temp_free_spots = 0
    ptr_simstats->temp_time_left = 0
END FUNCTION


FUNCTION save_final_dataset(ptr_simstats : SimStats*, ptr_output_file : FILE*)

    IF ptr_output_file == NULL
        RETURN
    ENDIF

    CALL fprintf(ptr_output_file,
        "%u,%u,%u,%u,%u,%u,%u,%u,%.2f,%u\n",
        ptr_simstats->total_exits,
        ptr_simstats->total_entries,
        ptr_simstats->total_queued,
        ptr_simstats->total_queue_time,
        ptr_simstats->total_parking_time,
        ptr_simstats->time_full_occupancy,
        ptr_simstats->peak_queue_length,
        ptr_simstats->step_longest_queue,
        ptr_simstats->peak_rel_occupancy,
        ptr_simstats->step_highest_occupancy)
END FUNCTION


FUNCTION close_output_file(FILE ptr_output_file)
    IF CALL flcose(ptr_output_file) = EOF
        RETURN -1
    ELSE
        RETURN 1
    END IF
END FUNCTION


FUNCTION reset_all_stats(SimStats (Adress)ptr_simstats)
    ptr_simstats->step_num = 0
    ptr_simstats->temp_exits = 0
    ptr_simstats->temp_entries = 0
    ptr_simstats->temp_rel_occupancy_percent = 0
    ptr_simstats->temp_queue_length = 0
    ptr_simstats->total_exits = 0
    ptr_simstats->total_entries = 0
    ptr_simstats->total_queued = 0
    ptr_simstats->total_queue_time = 0
    ptr_simstats->total_parking_time = 0
    ptr_simstats->time_full_occupancy = 0
    ptr_simstats->avg_rel_occupancy = 0.0
    ptr_simstats->peak_queue_length = 0
    ptr_simstats->step_longest_queue = 0
    ptr_simstats->peak_rel_occupancy = 0
    ptr_simstats->step_highest_occupancy = 0
END FUNCTION


FUNCTION free_stats(SimStats (Adress)ptr_simstats)
    CALL free(ptr_simstats)
END FUNCTION


END PSEUDOCODE
*/