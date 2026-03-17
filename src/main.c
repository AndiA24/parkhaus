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
#include "../include/utils.h"

int main() {

    initialize_ui();
    SimConfig *ptr_config = create_config();
    if (ptr_config == NULL) {
        output(2, "Error: Failed to create Config Struct. Simulation stopped.", 2, 1, NULL);
        return -1;
    }

    switch (get_config(ptr_config)) {
    case 1:
        output(2, "Info: Succesfully imported config from config-file.\n", 1, 0, NULL);
        break;
    case 0:
        output(2, "Couldn't find a config file. Falling back to default values\n", 4, 0, ptr_config);
        break;
    }

    SimStats *ptr_stats = init_simstats();
    if (ptr_stats == NULL) {
        output(2, "Error: Failed to initialize stats. Simulation stopped.", 2, 1, ptr_config);
        return -1;
    }
    

    while (1) {
        show_welcome(ptr_config);
        if (save_config(ptr_config) == -1) {
            output(2, "Error: Failed to create config file. Simulation stopped.", 2, 1, ptr_config);
            return -1;
        }
        if (run_simulation(ptr_config, ptr_stats) == -1) {
            output(2, "Error: Failed to run simulation. Simulation stopped.", 2, 1, ptr_config);
            return -1;
        }
    }
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