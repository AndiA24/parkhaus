/**
 * @file main.c
 * @brief Main Function of the Simulation.
 *
 * Function contains initialisation of the config, the programm loop
 * for the ui and a cleanup of memory after quit. 
 */

#include <stdio.h>

#include "../include/config.h"
#include "../include/stats.h"
#include "../include/ui.h"
#include "../include/simulation.h"

int run = 1;

int main(){

    initialize_ui();
    SimConfig *ptr_config = create_config();
    if(ptr_config == NULL){
        show_message(2, "Error: Failed to create Config Struct. Simulation Stopped.", 2, 1, NULL);
        return -1;
    }

    switch (get_config(ptr_config)){
    case 1:
        printf("Info: Succesfully imported config from config-file.\n");
        show_message(2, "Info: Succesfully imported config from config-file.", 4, 0, ptr_config);
        break;
    case 0:
        show_message(2, "Error: Failed to read config-file. Starting with default config.", 2, 0, ptr_config);
        break;
    }

    SimStats *ptr_stats = init_simstats();

    while(run == 1){
        show_welcome(ptr_config);
        save_config(ptr_config);
        run_simulation(ptr_config, ptr_stats);
    }

    free_stats(ptr_stats);
    free_config(ptr_config);
    return 0;
}

/*
PSEUDOCODE

run = 1

FUNCTION MAIN

    ptr_config = CALL create_config() // create config-struct
    CALL get_config((Adress)config) // read config from config file
    ptr_stats = CALL init_simstats() // Create stats-struct

    WHILE run DO:
        CALL show_welcome(ptr_config) // ask user for config changes

        // simulation started by user:
        CALL save_config(ptr_config)
        CALL run_simulation(ptr_config, ptr_stats)
    END WHILE

    CALL free_stats(ptr_stats)
    CALL free_config(ptr_config)

END FUNCTION

*/