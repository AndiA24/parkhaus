/**
 * @file test_config_populate_with_defaults.c
 * @brief Unit tests for the populate_with_default() function from config.c.
 *        Run with `make test_config_populate_with_defaults`.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/config.h"

int main() {
    SimConfig *ptr_config = NULL;

    // Test 1: All fields are set to the expected default values
    printf("Test 1: All fields are set to expected defaults: ");
    ptr_config = create_config();
    assert(ptr_config != NULL);
    int ret = populate_with_default(ptr_config);
    assert(ret == 0);
    assert(ptr_config->num_decks                    == 5);
    assert(ptr_config->spots_per_deck               == 60);
    assert(ptr_config->initial_occupancy            == 150);
    assert(ptr_config->max_parking_duration_steps   == 200);
    assert(ptr_config->min_parking_duration_steps   == 10);
    assert(ptr_config->sim_duration_steps           == 1000);
    assert(ptr_config->arrival_probability_percent  == 70);
    assert(strcmp(ptr_config->output_file_name, "parkhaus_results") == 0);
    assert(strcmp(ptr_config->config_file_name, "parkhaus_config.csv") == 0);
    assert(ptr_config->seed                         == 69);
    free_config(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    // Test 2: NULL pointer returns -1 and does not crash
    printf("Test 2: NULL pointer returns -1: ");
    ret = populate_with_default(NULL);
    assert(ret == -1);
    printf("OK\n");

    return 0;
}
