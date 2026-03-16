/**
 * @file test_config_get_config.c
 * @brief Unit tests for the get_config() function from config.c.
 *        Run with `make test_config_get_config`.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/config.h"
#include "../src/config.c"

int main() {
    SimConfig *ptr_config = NULL;

    // Test 1: Config file does not exist -> defaults are loaded, returns 0
    printf("Test 1: Missing config file loads defaults and returns 0: ");
    ptr_config = create_config();
    assert(ptr_config != NULL);
    strcpy(ptr_config->config_file_name, "nonexistent_test_config.csv");
    int ret = get_config(ptr_config);
    assert(ret == 0);
    assert(ptr_config->num_decks                   == 5);
    assert(ptr_config->spots_per_deck              == 60);
    assert(ptr_config->initial_occupancy           == 150);
    assert(ptr_config->max_parking_duration_steps  == 200);
    assert(ptr_config->min_parking_duration_steps  == 10);
    assert(ptr_config->sim_duration_steps          == 1000);
    assert(ptr_config->arrival_probability_percent == 70);
    assert(ptr_config->seed                        == 69);
    free_config(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    // Test 2: Valid config file -> values are read correctly, returns 1
    printf("Test 2: Valid config file is parsed correctly and returns 1: ");
    const char *test_file = "test_get_config_valid.csv";
    FILE *ptr_f = fopen(test_file, "w");
    assert(ptr_f != NULL);
    fprintf(ptr_f, "3,20,30,100,5,500,50,my_output,42\n");
    fclose(ptr_f);

    ptr_config = create_config();
    assert(ptr_config != NULL);
    strcpy(ptr_config->config_file_name, test_file);
    ret = get_config(ptr_config);
    assert(ret == 1);
    assert(ptr_config->num_decks                   == 3);
    assert(ptr_config->spots_per_deck              == 20);
    assert(ptr_config->initial_occupancy           == 30);
    assert(ptr_config->max_parking_duration_steps  == 100);
    assert(ptr_config->min_parking_duration_steps  == 5);
    assert(ptr_config->sim_duration_steps          == 500);
    assert(ptr_config->arrival_probability_percent == 50);
    assert(strcmp(ptr_config->output_file_name, "my_output") == 0);
    assert(ptr_config->seed                        == 42);
    free_config(ptr_config);
    ptr_config = NULL;
    remove(test_file);
    printf("OK\n");

    // Test 3: Malformed config file -> defaults are loaded, returns 0
    printf("Test 3: Malformed config file loads defaults and returns 0: ");
    test_file = "test_get_config_bad.csv";
    ptr_f = fopen(test_file, "w");
    assert(ptr_f != NULL);
    fprintf(ptr_f, "this,is,not,valid\n");
    fclose(ptr_f);

    ptr_config = create_config();
    assert(ptr_config != NULL);
    strcpy(ptr_config->config_file_name, test_file);
    ret = get_config(ptr_config);
    assert(ret == 0);
    assert(ptr_config->num_decks == 5);
    assert(ptr_config->sim_duration_steps == 1000);
    free_config(ptr_config);
    ptr_config = NULL;
    remove(test_file);
    printf("OK\n");

    return 0;
}
