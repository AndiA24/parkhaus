/**
 * @file test_config_save_config.c
 * @brief Unit tests for the save_config() function from config.c.
 *        Run with `make test_config_save_config`.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/config.h"

int main() {
    SimConfig *ptr_config = NULL;
    const char *test_file = "test_save_config_output.csv";
    FILE *ptr_f           = NULL;
    int ret;

    // Test 1: save_config writes a file that get_config can read back correctly
    printf("Test 1: Saved config is read back correctly: ");
    ptr_config = create_config();
    assert(ptr_config != NULL);
    strcpy(ptr_config->config_file_name, test_file);
    ptr_config->num_decks                   = 3;
    ptr_config->spots_per_deck              = 20;
    ptr_config->initial_occupancy           = 30;
    ptr_config->max_parking_duration_steps  = 100;
    ptr_config->min_parking_duration_steps  = 5;
    ptr_config->sim_duration_steps          = 500;
    ptr_config->arrival_probability_percent = 50;
    strcpy(ptr_config->output_file_name, "my_output");
    ptr_config->seed                        = 42;

    ret = save_config(ptr_config);
    assert(ret == 1);
    free_config(ptr_config);
    ptr_config = NULL;

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

    // Test 2: save_config overwrites an existing file with new values
    printf("Test 2: save_config overwrites existing file: ");
    ptr_f = fopen(test_file, "w");
    assert(ptr_f != NULL);
    fprintf(ptr_f, "9,99,99,99,99,99,99,old_output,99\n");
    fclose(ptr_f);

    ptr_config = create_config();
    assert(ptr_config != NULL);
    strcpy(ptr_config->config_file_name, test_file);
    ptr_config->num_decks                   = 2;
    ptr_config->spots_per_deck              = 10;
    ptr_config->initial_occupancy           = 5;
    ptr_config->max_parking_duration_steps  = 50;
    ptr_config->min_parking_duration_steps  = 2;
    ptr_config->sim_duration_steps          = 200;
    ptr_config->arrival_probability_percent = 30;
    strcpy(ptr_config->output_file_name, "new_output");
    ptr_config->seed                        = 7;

    ret = save_config(ptr_config);
    assert(ret == 0);
    free_config(ptr_config);
    ptr_config = NULL;

    ptr_config = create_config();
    assert(ptr_config != NULL);
    strcpy(ptr_config->config_file_name, test_file);
    ret = get_config(ptr_config);
    assert(ret == 1);
    assert(ptr_config->num_decks                   == 2);
    assert(ptr_config->spots_per_deck              == 10);
    assert(ptr_config->initial_occupancy           == 5);
    assert(ptr_config->max_parking_duration_steps  == 50);
    assert(ptr_config->min_parking_duration_steps  == 2);
    assert(ptr_config->sim_duration_steps          == 200);
    assert(ptr_config->arrival_probability_percent == 30);
    assert(strcmp(ptr_config->output_file_name, "new_output") == 0);
    assert(ptr_config->seed                        == 7);
    free_config(ptr_config);
    ptr_config = NULL;
    remove(test_file);
    printf("OK\n");

    return 0;
}
