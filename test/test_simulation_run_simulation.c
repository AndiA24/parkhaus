/**
 * @file test_simulation_run_simulation.c
 * @brief Unit tests for run_simulation() function, covering NULL guards
 *        and a successful minimal simulation run.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/simulation.h"
#include "../include/config.h"
#include "../include/stats.h"

static SimConfig *create_test_config() {
    SimConfig *ptr_config = calloc(1, sizeof(*ptr_config));
    ptr_config->num_decks = 1;
    ptr_config->spots_per_deck = 5;
    ptr_config->initial_occupancy = 0;
    ptr_config->max_parking_duration_steps = 10;
    ptr_config->min_parking_duration_steps = 1;
    ptr_config->sim_duration_steps = 0;
    ptr_config->arrival_probability_percent = 0;
    ptr_config->seed = 1;
    strncpy(ptr_config->output_file_name, "test_tmp_sim_output.csv",
            sizeof(ptr_config->output_file_name) - 1);
    return ptr_config;
}

static SimStats *create_test_stats() {
    SimStats *ptr_stats = calloc(1, sizeof(*ptr_stats));
    return ptr_stats;
}


int main() {
    SimConfig *ptr_config = NULL;
    SimStats  *ptr_stats  = NULL;

    // Test 1: NULL Guards
    printf("Test 1: NULL Guards: ");
    ptr_config = create_test_config();
    ptr_stats  = create_test_stats();
    assert(run_simulation(NULL, NULL)       == -1);
    assert(run_simulation(NULL, ptr_stats)  == -1);
    assert(run_simulation(ptr_config, NULL) == -1);
    free(ptr_config);
    free(ptr_stats);
    ptr_config = NULL;
    ptr_stats  = NULL;
    printf("OK\n");

    // Test 2: Minimal run (sim_duration_steps=0)
    //
    // Expected values after call:
    //   return value = 1
    //   output file exists on disk
    //   ptr_stats->step_num = 0 (reset_all_stats zeroes everything)
    printf("Test 2: Minimal Run: ");
    ptr_config = create_test_config();
    ptr_stats  = create_test_stats();
    remove(ptr_config->output_file_name);
    assert(run_simulation(ptr_config, ptr_stats) == 1);
    FILE *ptr_file = fopen(ptr_config->output_file_name, "r");
    assert(ptr_file != NULL);
    fclose(ptr_file);
    remove(ptr_config->output_file_name);
    assert(ptr_stats->step_num == 0);
    free(ptr_config);
    free(ptr_stats);
    ptr_config = NULL;
    ptr_stats  = NULL;
    printf("OK\n");

    return 0;
}