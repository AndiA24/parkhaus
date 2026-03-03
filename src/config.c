#include "../include/config.h"

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