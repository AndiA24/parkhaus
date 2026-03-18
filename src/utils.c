/**
 * @file utils.c
 * @brief Utility functions 
 *
 * This files contains two functions that had to be excluded from 
 * other files for better handling. One handles if we are testing or 
 * not and the appropriate output method. The other handles exiting
 * the program correcly.
 */


#include "../include/utils.h"
#include "../include/config.h"
#ifndef UNIT_TEST
#include "../include/ui.h"
#endif
#include <stdio.h>
#include <stdlib.h>

void output(int col, const char *ptr_msg, int color, int kill, SimConfig *ptr_config) {
#ifdef UNIT_TEST
    (void)col; (void)color; (void)kill; (void)ptr_config; //remove compiler warnings by voiding the values
    printf("%s", ptr_msg);
#else
    show_message(col, ptr_msg, color, kill, ptr_config);
#endif
}

void quit(SimConfig *ptr_config) {
    if (ptr_config) {
        save_config(ptr_config);
    }
    exit(1);
}
/*
FUNCTION quit(SimConfig *ptr_config)
    CALL  save_config(ptr_config)
    CALL exit()
END FUNCTION
*/
