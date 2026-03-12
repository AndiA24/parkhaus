/**
 * @file test_stats_reset_temp_stats.c
 * @brief Unit tests for the reset_temp_stats() function, covering NULL
 *        guards, correct reset of all temp stats, and keeping of all
 *        non temp stats.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/stats.h"

// helper function to create a SimStats struct for testing
// static to avoid collisions with similar functions in the main code
static SimStats *create_test_stats() {
    SimStats *ptr_stats = calloc(1, sizeof(*ptr_stats));
    if (ptr_stats == NULL) {
        printf("Error: Failed to allocate memory for the testing stats struct.\n");
    }
    return ptr_stats;
}

int main() {
    SimStats *ptr_stats = NULL;

    // Test 1: ptr_stats is NULL
    printf("Test 1: ptr_stats is NULL: ");
    assert(reset_temp_stats(NULL) == -1);
    printf("OK\n");

    // Test 2: All temporary fields are reset to 0
    //
    // Expected values after call:
    //   return value                   = 0
    //   temp_entries                   = 0
    //   temp_exits                     = 0
    //   temp_free_spots                = 0
    //   temp_queue_length              = 0
    //   temp_rel_occupancy_percent     = 0.0f
    //   temp_time_left                 = 0
    printf("Test 2: All temporary fields are reset to 0: ");
    ptr_stats = create_test_stats();
    ptr_stats->temp_entries = 5;
    ptr_stats->temp_exits = 3;
    ptr_stats->temp_free_spots = 40;
    ptr_stats->temp_queue_length = 7;
    ptr_stats->temp_rel_occupancy_percent = 60.0f;
    ptr_stats->temp_time_left = 12;
    assert(reset_temp_stats(ptr_stats) == 0);
    assert(ptr_stats->temp_entries == 0);
    assert(ptr_stats->temp_exits == 0);
    assert(ptr_stats->temp_free_spots == 0);
    assert(ptr_stats->temp_queue_length == 0);
    assert(ptr_stats->temp_rel_occupancy_percent == 0.0f);
    assert(ptr_stats->temp_time_left == 0);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    // Test 3: Non-temporary fields are not modified
    //
    // Expected values after call:
    //   return value           = 0
    //   step_num               = 10
    //   total_entries          = 20
    //   avg_rel_occupancy      = 75.0f
    //   peak_queue_length      = 8
    printf("Test 3: Non-temporary fields are not modified: ");
    ptr_stats = create_test_stats();
    ptr_stats->step_num = 10;
    ptr_stats->total_entries = 20;
    ptr_stats->avg_rel_occupancy = 75.0f;
    ptr_stats->peak_queue_length = 8;
    assert(reset_temp_stats(ptr_stats) == 0);
    assert(ptr_stats->step_num == 10);
    assert(ptr_stats->total_entries == 20);
    assert(ptr_stats->avg_rel_occupancy == 75.0f);
    assert(ptr_stats->peak_queue_length == 8);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    return 0;
}
