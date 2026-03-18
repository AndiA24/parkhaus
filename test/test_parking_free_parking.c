/**
 * @file test_parking_free_parking.c
 * @brief Unit tests for the free_parking() function, covering NULL
 *        guards and successful memory release.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/parking.h"

// helper function to create a Parking struct for testing
// static to avoid collisions with similar functions in the main code
static Parking *create_test_parking() {
    Parking *ptr_parking = calloc(1, sizeof(*ptr_parking));
    if (ptr_parking == NULL) {
        printf("Error: Failed to allocate memory for the testing parking struct.\n");
    }
    return ptr_parking;
}

SimStats *create_test_stats(){
    SimStats *ptr_stats = calloc(1, sizeof *ptr_stats);
    return ptr_stats;
}

int main() {
    Parking *ptr_parking = NULL;
    SimStats *ptr_stats = NULL;

    // Test 1: ptr_parking is NULL
    printf("Test 1: ptr_parking is NULL: ");
    assert(free_parking(NULL, NULL) == -1);
    printf("OK\n");

    // Test 2: Valid pointer is freed successfully
    //
    // Expected values after call:
    //   return value = 0
    printf("Test 2: Valid pointer is freed successfully: ");
    ptr_parking = create_test_parking();
    ptr_stats = create_test_stats();
    assert(free_parking(ptr_parking, ptr_stats) == 0);
    free(ptr_stats);
    ptr_parking = NULL;
    ptr_stats = NULL;
    printf("OK\n");

    return 0;
}