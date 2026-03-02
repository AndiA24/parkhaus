#ifndef UI_H
#define UI_H

#include "stats.h"
#include "config.h"

void show_welcome(SimConfig *ptr_config);

void show_settings(SimConfig *ptr_config);

void prompt_input(char text[], void *ptr_current_value, long min, long max);

void render_settings(SimConfig *ptr_config);

void show_running(SimStats *ptr_stats);

void show_results(SimStats *ptr_stats);

#endif