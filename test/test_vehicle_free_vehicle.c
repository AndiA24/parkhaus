/**
 * @file test_vehicle_free_vehicle.c
 * @brief Unit tests for the free_vehicle() function, covering NULL
 *        guards and successful memory release.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/vehicle.h"

// helper function to create a Vehicle struct for testing
// static to avoid collisions with similar functions in the main code
static Vehicle *create_test_vehicle() {
    Vehicle *ptr_vehicle = calloc(1, sizeof(*ptr_vehicle));
    if (ptr_vehicle == NULL) {
        printf("Error: Failed to allocate memory for the testing vehicle struct.\n");
    }
    return ptr_vehicle;
}

int main() {
    Vehicle *ptr_vehicle = NULL;

    // Test 1: ptr_vehicle is NULL
    printf("Test 1: ptr_vehicle is NULL: ");
    assert(free_vehicle(NULL) == -1);
    printf("OK\n");

    // Test 2: Valid pointer is freed successfully
    //
    // Expected values after call:
    //   return value = 0
    printf("Test 2: Valid pointer is freed successfully: ");
    ptr_vehicle = create_test_vehicle();
    assert(free_vehicle(ptr_vehicle) == 0);
    ptr_vehicle = NULL;
    printf("OK\n");

    return 0;
}