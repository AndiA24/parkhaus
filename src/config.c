/**
 * @file config.c
 * @brief Simulation configuration management.
 *
 * Provides functions to create, load from external config file, save, 
 * and free the simulation configuration.
 * If no config file is found, default values are used.
 */

#include "../include/config.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_DECKS_DEFAULT 5
#define SPOTS_PER_DECK_DEFAULT 60
#define INITIAL_OCCUPANCY_DEFAULT 150
#define MAX_PARKING_DURATION_DEFAULT 200
#define MIN_PARKING_DURATION_DEFAULT 10
#define SIM_DURATION_STEPS_DEFAULT 1000
#define ARRIVAL_PERCENT_DEFAULT 70
#define OUTPUT_FILE_NAME_DEFAULT "parkhaus_results"
#define CONFIG_FILE_NAME_DEFAULT "parkhaus_config.csv"
#define SEED_DEFAULT 69


int populate_with_default(SimConfig *ptr_config) {
    if(ptr_config == NULL) {
        return -1;
    }
    ptr_config->num_decks = NUM_DECKS_DEFAULT;
    ptr_config->spots_per_deck = SPOTS_PER_DECK_DEFAULT;
    ptr_config->initial_occupancy = INITIAL_OCCUPANCY_DEFAULT;
    ptr_config->max_parking_duration_steps = MAX_PARKING_DURATION_DEFAULT;
    ptr_config->min_parking_duration_steps = MIN_PARKING_DURATION_DEFAULT;
    ptr_config->sim_duration_steps = SIM_DURATION_STEPS_DEFAULT;
    ptr_config->arrival_probability_percent = ARRIVAL_PERCENT_DEFAULT;
    strcpy(ptr_config->output_file_name, OUTPUT_FILE_NAME_DEFAULT);
    strcpy(ptr_config->config_file_name, CONFIG_FILE_NAME_DEFAULT);
    ptr_config->seed = SEED_DEFAULT;
    return 0;
}

SimConfig *create_config() {
    SimConfig *ptr_config = calloc(1, sizeof(*ptr_config));
    if(ptr_config == NULL) {
        return NULL;
    }
    strcpy(ptr_config->config_file_name, CONFIG_FILE_NAME_DEFAULT);
    return ptr_config;
}

int get_config(SimConfig *ptr_config) {
    FILE *ptr_f = fopen(ptr_config->config_file_name, "r");
    if(!ptr_f) {
        populate_with_default(ptr_config);
        return 0;
    }
    else {
        int count = fscanf(ptr_f, "%u,%u,%u,%u,%u,%u,%u,%69[^,],%u",
        &ptr_config->num_decks,
        &ptr_config->spots_per_deck,
        &ptr_config->initial_occupancy,
        &ptr_config->max_parking_duration_steps,
        &ptr_config->min_parking_duration_steps,
        &ptr_config->sim_duration_steps,
        &ptr_config->arrival_probability_percent,
        ptr_config->output_file_name,
        &ptr_config->seed);
        if(count != 9) {
            populate_with_default(ptr_config);
            fclose(ptr_f);
            return 0;
        }
        else {
            fclose(ptr_f);
            return 1;
        }
    }
}

int save_config(SimConfig *ptr_config) {
    FILE *ptr_check = fopen(ptr_config->config_file_name, "r");
    int file_existed = 0;
    if(ptr_check != NULL) {
        file_existed = 1;
        fclose(ptr_check);
    }

    FILE *ptr_f = fopen(ptr_config->config_file_name, "w");
    if(!ptr_f) {
        return -1;
    }

    fprintf(ptr_f, "%u,%u,%u,%u,%u,%u,%u,%s,%u\n",
        ptr_config->num_decks,
        ptr_config->spots_per_deck,
        ptr_config->initial_occupancy,
        ptr_config->max_parking_duration_steps,
        ptr_config->min_parking_duration_steps,
        ptr_config->sim_duration_steps,
        ptr_config->arrival_probability_percent,
        ptr_config->output_file_name,
        ptr_config->seed);
    fclose(ptr_f);
    if(file_existed) {
        return 0;
    }
    return 1;
}

int free_config(SimConfig *ptr_config) {
    if(ptr_config == NULL){
        //commented it out because the user is already closing when this is called so doesn't really matter but left it here if we decide to add it back.
        //output(2, "Error: Failed to free config Struct. Invalid Argument\n", 2, 0, NULL);
        return -1;
    }
    free(ptr_config);
    return 0;
}

/*
PSEUDOCODE

DEFINE CONFIG_FIELD_COUNT = 10   // number of fields in SimConfig

FUNCTION create_config() RETURNS SimConfig*
    ptr_config : SimConfig*
    ptr_config = CALL calloc(1, CALL sizeof *ptr_config)    //allocate memory with default values

    IF ptr_config == NULL THEN                                   
        RETURN NULL
    END IF
    RETURN ptr_config
END FUNCTION


FUNCTION get_config(SimConfig *ptr_config)
    IF ptr_config == NULL THEN
        RETURN
    END IF

    ptr_config_file : FILE*
    ptr_config_file = CALL fopen(ptr_config->config_file_name, "r")

    IF ptr_config_file == NULL THEN
        RETURN
    END IF

    fields_read : int
    fields_read<-CALL fscanf(ptr_config_file, "%u,%u,%u,%u,%u,%u,%u,%69[^,],%u",
        &ptr_config->num_decks,
        &ptr_config->spots_per_deck,
        &ptr_config->initial_occupancy,
        &ptr_config->max_parking_duration_steps,
        &ptr_config->min_parking_duration_steps,
        &ptr_config->sim_duration_steps,
        &ptr_config->arrival_probability_percent,
        ptr_config->output_file_name,
        &ptr_config->seed)

    CALL fclose(ptr_config_file)

    IF fields_read != CONFIG_FIELD_COUNT THEN
        RETURN
    END IF
END FUNCTION


FUNCTION save_config(ptr_config : SimConfig*)
    IF ptr_config == NULL THEN
        RETURN
    END IF

    ptr_file : FILE*
    ptr_file = CALL fopen(ptr_config->config_file_name, "w") //fopen erstell auch ein file wenn keins existiert also müssen wir das nicht selber machen

    IF ptr_file == NULL THEN
        RETURN
    END IF

    CALL fprintf(ptr_file, "%u,%u,%u,%u,%u,%u,%u,%s,%s,%u\n",
        ptr_config->num_decks,
        ptr_config->spots_per_deck,
        ptr_config->initial_occupancy,
        ptr_config->max_parking_duration_steps,
        ptr_config->min_parking_duration_steps,
        ptr_config->sim_duration_steps,
        ptr_config->arrival_probability_percent,
        ptr_config->output_file_name,
        ptr_config->config_file_name,
        ptr_config->seed)
    CALL fclose(ptr_file)
END FUNCTION



FUNCTION free_config(ptr_config : SimConfig*)
    IF ptr_config == NULL THEN                                   
        RETURN 
    END IF
    CALL free(ptr_config)
END FUNCTION

*/