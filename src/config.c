#include "../include/config.h"

/*
PSEUDOCODE

FUNCTION create_config() RETURNS SimConfig*
    ptr_config : SimConfig*
    ptr_config = CALL calloc(1, CALL sizeof *ptr_config)    //allocate memory with default values

    IF ptr_config == NULL THEN                                   
        RETURN NULL

    RETURN ptr_config
END FUNCTION


FUNCTION get_config(ptr_simstats: SimStats*)
    IF ptr_config == NULL THEN                                   
        RETURN 

    ptr_config_file : FILE*
    ptr_config_file = CALL fopen(ptr_config->config_file_name, "r")

    IF ptr_config_file == NULL THEN
        RETURN

    

END FUNCTION


FUNCTION save_config()

END FUNCTION


FUNCTION free_config(ptr_config : SimConfig*)

    IF ptr_config == NULL THEN                                   
        RETURN 

    CALL free(ptr_config)
END FUNCTION

*/