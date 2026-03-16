/**
 * @file test_config_create_config.c
 * @brief Unit tests for the create_config() function from config.c.
 *        Run with `make test_config_create_config`.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/config.h"
#include "../src/config.c"

int main() {
    SimConfig *ptr_config = NULL;

    // Test 1: Return value is not NULL
    printf("Test 1: Return value is not NULL: ");
    ptr_config = create_config();
    assert(ptr_config != NULL);
    free_config(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    // Test 2: config_file_name is set, all other fields are zero
    printf("Test 2: config_file_name set, numeric fields zero-initialized: ");
    ptr_config = create_config();
    assert(ptr_config != NULL);
    assert(strcmp(ptr_config->config_file_name, "parkhaus_config.csv") == 0);
    assert(ptr_config->num_decks                   == 0);
    assert(ptr_config->spots_per_deck              == 0);
    assert(ptr_config->initial_occupancy           == 0);
    assert(ptr_config->max_parking_duration_steps  == 0);
    assert(ptr_config->min_parking_duration_steps  == 0);
    assert(ptr_config->sim_duration_steps          == 0);
    assert(ptr_config->arrival_probability_percent == 0);
    assert(ptr_config->seed                        == 0);
    free_config(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    return 0;
}
