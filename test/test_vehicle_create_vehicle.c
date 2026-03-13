/**
 * @file test_vehicle_create_vehicle.c
 * @brief Unit tests for the create_vehicle() function, covering successful
 *        allocation, correct assignments of all contained values and increment
 *        of id_count in stats-struct.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/vehicle.h"
#include "../include/stats.h"
#include "../include/config.h"

// helper function to create a SimStats struct for testing
// static to avoid collisions with similar functions in the main code
static SimStats *create_test_stats() {
    SimStats *ptr_stats = calloc(1, sizeof(*ptr_stats));
    if (ptr_stats == NULL) {
        printf("Error: Failed to allocate memory for the testing stats struct.\n");
    }
    return ptr_stats;
}

// helper function to create a SimConfig struct for testing
// static to avoid collisions with similar functions in the main code
static SimConfig *create_test_config() {
    SimConfig *ptr_config = calloc(1, sizeof(*ptr_config));
    if (ptr_config == NULL) {
        printf("Error: Failed to allocate memory for the testing config struct.\n");
    }
    return ptr_config;
}

int main() {
    SimStats  *ptr_stats  = NULL;
    SimConfig *ptr_config = NULL;
    Vehicle   *ptr_vehicle = NULL;

    // Test 1: NULL-Guards 
    printf("Test 1: NULL Guards: ");
    ptr_stats  = create_test_stats();
    ptr_config = create_test_config();
    assert(create_vehicle(NULL, ptr_config) == NULL);
    assert(create_vehicle(ptr_stats, NULL) == NULL);
    free(ptr_stats);
    ptr_stats = NULL;
    free(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    // Test 2: Valid vehicle is created with correct values
    //
    // Expected values:
    //   ptr_vehicle                    != NULL
    //   ptr_vehicle->parking_duration  between min and max
    //   ptr_vehicle->entry_time        = 0 (beacuse entry_time is set in entry_parking())
    //   ptr_vehicle->id                = ptr_stats->id_count
    //   ptr_vehicle->queue_time        = 0
    printf("Test 2: Valid vehicle is created: ");
    ptr_stats  = create_test_stats();
    ptr_config = create_test_config();
    ptr_stats->step_num = 20;
    ptr_stats->id_count = 21;
    ptr_config->min_parking_duration_steps = 1;
    ptr_config->max_parking_duration_steps = 10;
    ptr_vehicle = create_vehicle(ptr_stats, ptr_config);
    assert(ptr_vehicle != NULL);
    assert(ptr_vehicle->parking_duration <= 10);
    assert(ptr_vehicle->parking_duration >= 1);
    assert(ptr_vehicle->entry_time == 0);
    assert(ptr_vehicle->id == 21);
    assert(ptr_vehicle->queue_time == 0);
    free_vehicle(ptr_vehicle);
    ptr_vehicle = NULL;
    free(ptr_stats);
    ptr_stats = NULL;
    free(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    // Test 3: ID id_count is incremented
    //
    // Expected values after call:
    //   ptr_stats->id_count = 6
    printf("Test 3: id_count is incremented: ");
    ptr_stats  = create_test_stats();
    ptr_config = create_test_config();
    ptr_config->min_parking_duration_steps = 1;
    ptr_config->max_parking_duration_steps = 10;
    ptr_stats->id_count = 5;
    ptr_vehicle = create_vehicle(ptr_stats, ptr_config);
    assert(ptr_stats->id_count == 6);
    free_vehicle(ptr_vehicle);
    ptr_vehicle = NULL;
    free(ptr_stats);
    ptr_stats = NULL;
    free(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    return 0;
}
