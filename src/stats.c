#include "../include/stats.h"
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
    output_file : FILE*

    DO
        output_file = fopen(ptr_config->output_file_name, "r")

        IF output_file != NULL
            fclose(output_file)
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

    output_file = fopen(ptr_config->output_file_name, "w")

    IF output_file == NULL
        RETURN NULL
    ENDIF

    // Write configuration values
    CALL fprintf(output_file, "%u\n", ptr_config->num_decks)
    CALL fprintf(output_file, "%u\n", ptr_config->spots_per_deck)
    CALL fprintf(output_file, "%u\n", ptr_config->initial_occupancy)
    CALL fprintf(output_file, "%u\n", ptr_config->max_parking_duration_steps)
    CALL fprintf(output_file, "%u\n", ptr_config->min_parking_duration_steps)
    CALL fprintf(output_file, "%u\n", ptr_config->sim_duration_steps)
    CALL fprintf(output_file, "%u\n", ptr_config->arrival_probability_percent)
    CALL fprintf(output_file, "%s\n", ptr_config->output_file_name)
    CALL fprintf(output_file, "%u\n", ptr_config->seed)

    RETURN output_file
END FUNCTION

FUNCTION update_simstats()
    
    

    return ptr_output_file

END FUNCTION

FUNCTION save_temp_dataset()

END FUNCTION


FUNCTION save_final_dataset()

END FUNCTION

END PSEUDOCODE
*/