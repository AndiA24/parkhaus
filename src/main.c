/*
PSEUDOCODE

main(){

    config = CALL create_config() // create config-struct
    CALL get_config((Adress)config) // read config from config file
    stats = CALL init_simstats // Create stats-struct

    WHILE run DO:
        XXX // ask user for config changes

        // simulation started by user:
        CALL save_config
        CALL run_simulation()
        CALL reset_all_stats
    END WHILE

    CALL free_stats()
    CALL free_config()

}

*/