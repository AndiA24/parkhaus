/**
 * @file test_stats_free_stats.c
 * @brief Unit tests for the free_stats() function, covering NULL
 *        guards and successful memory release.
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
    assert(free_stats(NULL) == -1);
    printf("OK\n");

    // Test 2: Valid pointer is freeed successfully
    //
    // Expected values after call:
    //   return value = 0
    printf("Test 2: Valid pointer is freed successfully: ");
    ptr_stats = create_test_stats();
    assert(free_stats(ptr_stats) == 0);
    ptr_stats = NULL;
    printf("OK\n");

    return 0;
}
