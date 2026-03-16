#include "../include/utils.h"
#include "../include/config.h"
#ifndef UNIT_TEST
#include "../include/ui.h"
#endif
#include <stdio.h>
#include <stdlib.h>

void output(int col, const char *ptr_msg, int color, int kill, SimConfig *ptr_config) {
#ifdef UNIT_TEST
    (void)col; (void)color; (void)kill; (void)ptr_config;
    printf("%s", ptr_msg);
#else
    show_message(col, ptr_msg, color, kill, ptr_config);
#endif
}

void quit(SimConfig *ptr_config) {
    save_config(ptr_config);
    exit(1);
}
/*
FUNCTION quit(SimConfig *ptr_config)
    CALL  save_config(ptr_config)
    CALL exit()
END FUNCTION
*/
