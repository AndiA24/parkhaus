/**
 * @file test_stats_update_stats.c
 * @brief Unit tests for the update_simstats() function, covering NULL
 *        guards and correct calculation of all statistics fields.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/stats.h"
#include "../include/parking.h"
#include "../include/queue.h"
#include "../include/vehicle.h"

// help functions to create necessary structs to test the function using
// static to avoid collisions with similar structs in the main code
static Parking *create_test_parking(unsigned int total_capacity, unsigned int occupied_count) {
    Parking *ptr_parking = calloc(1, sizeof(*ptr_parking));
    ptr_parking->total_capacity = total_capacity;
    ptr_parking->occupied_count = occupied_count;
    ptr_parking->decks = 0;
    ptr_parking->ptr_decks = NULL;
    return ptr_parking;
}

static Queue *create_test_queue(int size) {
    Queue *ptr_queue = calloc(1, sizeof(*ptr_queue));
    ptr_queue->size = size;
    ptr_queue->ptr_head = NULL;
    ptr_queue->ptr_tail = NULL;
    return ptr_queue;
}

int main() {
    SimStats *ptr_stats = NULL;
    Parking *ptr_parking = NULL;
    Queue *ptr_queue = NULL;

    // Test 1: ptr_stats is NULL
    printf("Test 1: ptr_stats is NULL: ");
    ptr_parking = create_test_parking(100, 50);
    ptr_queue = create_test_queue(3);
    assert(update_simstats(NULL, ptr_parking, ptr_queue) == -1);
    free(ptr_parking); 
    free(ptr_queue);   
    ptr_parking = NULL;
    ptr_queue = NULL;
    printf("OK\n");

    // Test 2: ptr_parking is NULL
    printf("Test 2: ptr_parking is NULL: ");
    ptr_stats = init_simstats();
    ptr_queue = create_test_queue(3);
    assert(update_simstats(ptr_stats, NULL, ptr_queue) == -1);
    free_stats(ptr_stats); 
    free(ptr_queue);
    ptr_stats = NULL;
    ptr_queue = NULL;
    printf("OK\n");

    // Test 3: ptr_queue is NULL
    printf("Test 3: ptr_queue is NULL: ");
    ptr_stats = init_simstats();
    ptr_parking = create_test_parking(100, 50);
    assert(update_simstats(ptr_stats, ptr_parking, NULL) == -1);
    free_stats(ptr_stats); 
    free(ptr_parking);     
    ptr_stats = NULL;
    ptr_parking = NULL;
    printf("OK\n");

    // Test 4: Check calculated values for testing input (capacity=100, occupied=60, queue_size=3)
    //
    // Expected values after the first call (step_num=0, avg_rel_occupancy=0.0):
    //   return value               = 1
    //   temp_rel_occupancy_percent = 60.0f
    //   temp_queue_length          = 3
    //   temp_free_spots            = 40
    //   avg_rel_occupancy          = 60.0f
    printf("Test 4: All computed fields with valid structs: ");
    ptr_stats = init_simstats();
    ptr_parking = create_test_parking(100, 60);
    ptr_queue = create_test_queue(3);

    assert(update_simstats(ptr_stats, ptr_parking, ptr_queue) == 1);
    assert(ptr_stats->temp_rel_occupancy_percent == 60.0f);
    assert(ptr_stats->temp_queue_length == 3);
    assert(ptr_stats->temp_free_spots == 40);
    assert(ptr_stats->avg_rel_occupancy == 60.0f);
    assert(ptr_stats->time_full_occupancy == 0);

    // second call: every spot occupied, time_full_occupancy should increase
    ptr_stats->step_num = 1;
    ptr_parking->occupied_count = 100;
    assert(update_simstats(ptr_stats, ptr_parking, ptr_queue) == 1);
    assert(ptr_stats->time_full_occupancy == 1);

    free_stats(ptr_stats);
    free(ptr_parking);
    free(ptr_queue);
    ptr_stats = NULL;
    ptr_parking = NULL;
    ptr_queue = NULL;
    printf("OK\n");

    return 0;
}
