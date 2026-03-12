/**
 * @file test_stats_update_peak.c
 * @brief Unit tests for the update_peak() function, covering NULL
 *        guards and correct update behaviour for both peak fields.
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
    assert(update_peak(NULL) == -1);
    printf("OK\n");

    // Test 2: temp_rel_occupancy_percent and temp_queue lenght exceeds peak
    //
    // Expected values after call
    //
    //  return value            = 1
    //  peak_rel_occupancy      = 80.0
    //  step_highest_occupancy  = 5
    //  peak_queue_lenght       = 4
    //  step_longest_queue      = 5
    printf("Test 2: temp_rel_occupancy_percent and temp_queue_lenght exceeds peak: ");
    ptr_stats = create_test_stats();
    ptr_stats->step_num = 5;
    ptr_stats->temp_rel_occupancy_percent = 80.0f;
    ptr_stats->peak_rel_occupancy = 60.0f;
    ptr_stats->temp_queue_length = 4;
    ptr_stats->peak_queue_length = 3;
    assert(update_peak(ptr_stats) == 1);
    assert(ptr_stats->peak_rel_occupancy == 80.0f);
    assert(ptr_stats->step_highest_occupancy == 5);
    assert(ptr_stats->peak_queue_length == 4);
    assert(ptr_stats->step_longest_queue == 5);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    // Test 3: temp_rel_occupancy_percent and temp_queue_lenght equals peak
    //
    // Expected values after call
    //
    //  return value            = 1
    //  peak_rel_occupancy      = 60.0f
    //  step_highest_occupancy  = 0 
    //  peak_queue_lenght       = 1
    //  step_longest_queue      = 2
    printf("Test 3: temp_rel_occupancy_percent and temp_queue_lenght equals peak (no update): ");
    ptr_stats = create_test_stats();
    ptr_stats->step_num = 3;
    ptr_stats->step_highest_occupancy = 1;
    ptr_stats->peak_rel_occupancy = 60.0f;
    ptr_stats->temp_rel_occupancy_percent = 60.0f;
    ptr_stats->step_longest_queue = 2;
    ptr_stats->peak_queue_length = 1;
    ptr_stats->temp_queue_length = 1;

    assert(update_peak(ptr_stats) == 1);
    assert(ptr_stats->peak_rel_occupancy == 60.0f);
    assert(ptr_stats->step_highest_occupancy == 1);
    assert(ptr_stats->peak_queue_length == 1),
    assert(ptr_stats->step_longest_queue == 2);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    return 0;
}
