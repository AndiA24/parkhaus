#include "../include/utils.h"
#include "../include/config.h"
#include <stdlib.h>

void quit(SimConfig *ptr_config) {
    //save_config(ptr_config);
    exit(1);
}
/*
FUNCTION quit(SimConfig *ptr_config)
    CALL  save_config(ptr_config)
    CALL exit()
END FUNCTION
*/