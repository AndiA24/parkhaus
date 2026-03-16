/**
 * @file test_stats_init_stats.c
 * @brief Unit tests for the init_simstats() function, covering successful
 *        allocation, zero-initialization of all fields, and pointer independence.
 *        Run with `make test_init_stats`.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/stats.h"
#include "../include/config.h"
#include "../include/queue.h"
#include "../include/parking.h"

int main(){
    SimStats *ptr_stats  = NULL;
    SimStats *ptr_stats2 = NULL;

    // Test 1: Return value is not NULL
    printf("Test 1: Return value is not NULL: ");
    ptr_stats = init_simstats(NULL);
    assert(ptr_stats != NULL);
    free_stats(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    // Test 2: All fields are zero-initialized
    printf("Test 2: All fields are zero after init: ");
    ptr_stats = init_simstats(NULL);
    assert(ptr_stats != NULL);
    assert(ptr_stats->step_num                   == 0);
    assert(ptr_stats->id_count                   == 0);
    assert(ptr_stats->temp_exits                 == 0);
    assert(ptr_stats->temp_entries               == 0);
    assert(ptr_stats->temp_rel_occupancy_percent == 0.0f);
    assert(ptr_stats->temp_queue_length          == 0);
    assert(ptr_stats->temp_free_spots            == 0);
    assert(ptr_stats->temp_time_left             == 0);
    assert(ptr_stats->total_exits                == 0);
    assert(ptr_stats->total_entries              == 0);
    assert(ptr_stats->total_queued               == 0);
    assert(ptr_stats->total_queue_time           == 0);
    assert(ptr_stats->total_parking_time         == 0);
    assert(ptr_stats->time_full_occupancy        == 0);
    assert(ptr_stats->avg_rel_occupancy          == 0.0f);
    assert(ptr_stats->peak_queue_length          == 0);
    assert(ptr_stats->step_longest_queue         == 0);
    assert(ptr_stats->peak_rel_occupancy         == 0.0f);
    assert(ptr_stats->step_highest_occupancy     == 0);
    free_stats(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    // Test 3: Two calls return independent pointers
    printf("Test 3: Two calls return different pointers: ");
    ptr_stats  = init_simstats(NULL);
    ptr_stats2 = init_simstats(NULL);
    assert(ptr_stats  != NULL);
    assert(ptr_stats2 != NULL);
    assert(ptr_stats  != ptr_stats2);
    free_stats(ptr_stats);
    free_stats(ptr_stats2);
    ptr_stats  = NULL;
    ptr_stats2 = NULL;
    printf("OK\n");

    return 0;
}
