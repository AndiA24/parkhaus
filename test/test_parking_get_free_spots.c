/**
 * @file test_parking_get_free_spots.c
 * @brief Unit tests for the get_free_spots() function, covering NULL guards
 *        and correct calculation of free spots.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/parking.h"
#include "../include/stats.h"

static Parking *create_test_parking(unsigned int total_capacity, unsigned int occupied_count) {
    Parking *ptr_parking = calloc(1, sizeof(*ptr_parking));
    ptr_parking->total_capacity = total_capacity;
    ptr_parking->occupied_count = occupied_count;
    return ptr_parking;
}

static SimStats *create_test_stats() {
    SimStats *ptr_stats = calloc(1, sizeof(*ptr_stats));
    return ptr_stats;
}


int main() {
    Parking *ptr_parking = NULL;
    SimStats *ptr_stats = NULL;

    // Test 1: NULL Guards
    printf("Test 1: NULL Guards: ");
    ptr_parking = create_test_parking(100, 0);
    ptr_stats = create_test_stats();
    assert(get_free_spots(NULL, NULL) == -1);
    assert(get_free_spots(NULL, ptr_stats) == -1);
    assert(get_free_spots(ptr_parking, NULL) == -1);
    free(ptr_parking);
    free(ptr_stats);
    ptr_parking = NULL; 
    ptr_stats = NULL;
    printf("OK\n");

    // Test 2: Correct calculation of free spots
    //
    // Expected values after call:
    //   return value = 1
    //   stats->temp_free_spots = total_capacity - occupied_count (= 40)
    printf("Test 2: Correct free spots calculation: ");
    ptr_parking = create_test_parking(100, 60);
    ptr_stats = create_test_stats();
    assert(get_free_spots(ptr_parking, ptr_stats) == 1);
    assert(ptr_stats->temp_free_spots == 40);
    free(ptr_parking);
    free(ptr_stats);
    ptr_parking = NULL; 
    ptr_stats = NULL;
    printf("OK\n");

    return 0;
}