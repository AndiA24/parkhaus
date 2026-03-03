#include "../include/config.h"
#include "../include/stats.h"
#include "../include/ui.h"
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