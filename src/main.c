#include <stdio.h>

#include "../include/config.h"
#include "../include/stats.h"
#include "../include/ui.h"
#include "../include/simulation.h"

int run = 1;

int main(){

    SimConfig *ptr_config = create_config();
    if(create_config() == NULL){
        printf("Error: Failed to create Config Struct. Simulation Stopped.\n");
        return -1;
    }

    switch (get_config(ptr_config)){
    case 1:
        printf("Info: Succesfully imported config from config-file.\n");
        break;
    case 0:
        printf("Info: Failed to read config-file. Starting with default config.\n");
        break;
    case -1:
        printf("Error: Failed to load config. Simulation Stopped.\n");
        return -1;
        break;
    }

    SimStats *ptr_stats = init_simstats();

    while(run == 1){
        
    }

    free_stats(ptr_stats);
    free_config(ptr_config);
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