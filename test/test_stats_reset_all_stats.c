/**
 * @file test_stats_reset_all_stats.c
 * @brief Unit tests for the reset_all_stats() function, covering NULL
 *        guards and correct reset of all stats values.
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
    assert(reset_all_stats(NULL) == -1);
    printf("OK\n");

    // Test 2: All fields are reset to 0
    //
    // Expected values after call:
    //   return value                   = 0
    //   step_num                       = 0
    //   id_count                       = 0
    //   temp_entries                   = 0
    //   temp_exits                     = 0
    //   temp_free_spots                = 0
    //   temp_queue_length              = 0
    //   temp_rel_occupancy_percent     = 0.0f
    //   temp_time_left                 = 0
    //   total_entries                  = 0
    //   total_exits                    = 0
    //   total_queued                   = 0
    //   total_queue_time               = 0
    //   total_parking_time             = 0
    //   time_full_occupancy            = 0
    //   avg_rel_occupancy              = 0.0f
    //   peak_queue_length              = 0
    //   step_longest_queue             = 0
    //   peak_rel_occupancy             = 0.0f
    //   step_highest_occupancy         = 0
    printf("Test 2: All fields are reset to 0: ");
    ptr_stats = create_test_stats();
    ptr_stats->step_num = 10;
    ptr_stats->id_count = 42;
    ptr_stats->temp_entries = 5;
    ptr_stats->temp_exits = 3;
    ptr_stats->temp_free_spots = 40;
    ptr_stats->temp_queue_length = 7;
    ptr_stats->temp_rel_occupancy_percent = 60.0f;
    ptr_stats->temp_time_left = 12;
    ptr_stats->total_entries = 20;
    ptr_stats->total_exits = 18;
    ptr_stats->total_queued = 5;
    ptr_stats->total_queue_time = 15;
    ptr_stats->total_parking_time = 200;
    ptr_stats->time_full_occupancy = 3;
    ptr_stats->avg_rel_occupancy = 75.0f;
    ptr_stats->peak_queue_length = 8;
    ptr_stats->step_longest_queue = 7;
    ptr_stats->peak_rel_occupancy = 95.0f;
    ptr_stats->step_highest_occupancy = 9;
    assert(reset_all_stats(ptr_stats) == 0);
    assert(ptr_stats->step_num == 0);
    assert(ptr_stats->id_count == 0);
    assert(ptr_stats->temp_entries == 0);
    assert(ptr_stats->temp_exits == 0);
    assert(ptr_stats->temp_free_spots == 0);
    assert(ptr_stats->temp_queue_length == 0);
    assert(ptr_stats->temp_rel_occupancy_percent == 0.0f);
    assert(ptr_stats->temp_time_left == 0);
    assert(ptr_stats->total_entries == 0);
    assert(ptr_stats->total_exits == 0);
    assert(ptr_stats->total_queued == 0);
    assert(ptr_stats->total_queue_time == 0);
    assert(ptr_stats->total_parking_time == 0);
    assert(ptr_stats->time_full_occupancy == 0);
    assert(ptr_stats->avg_rel_occupancy == 0.0f);
    assert(ptr_stats->peak_queue_length == 0);
    assert(ptr_stats->step_longest_queue == 0);
    assert(ptr_stats->peak_rel_occupancy == 0.0f);
    assert(ptr_stats->step_highest_occupancy == 0);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    return 0;
}
