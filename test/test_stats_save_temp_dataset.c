/**
 * @file test_stats_save_temp_dataset.c
 * @brief Unit tests for the save_temp_dataset() function, covering NULL Guards
 *        and check successful write of per-step statistics to file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/stats.h"

static SimStats *create_test_stats() {
    SimStats *ptr_stats = calloc(1, sizeof(*ptr_stats));
    return ptr_stats;
}


int main() {
    SimStats *ptr_stats = NULL;
    FILE *ptr_file = NULL;

    // Test 1: NULL Guards
    printf("Test 1: NULL Guards: ");
    ptr_stats = create_test_stats();
    ptr_file = tmpfile();
    assert(save_temp_dataset(NULL, NULL) == -1);
    assert(save_temp_dataset(NULL, ptr_file) == -1);
    assert(save_temp_dataset(ptr_stats, NULL) == -1);
    fclose(ptr_file);
    free(ptr_stats);
    ptr_stats = NULL; 
    ptr_file = NULL;
    printf("OK\n");

    // Test 2: Valid Arguments
    //
    // Expected values after call:
    //   return value = 1
    //   file contains one line of CSV data
    printf("Test 2: Valid Arguments: ");
    ptr_stats = create_test_stats();
    ptr_stats->temp_exits = 2;
    ptr_stats->temp_entries = 3;
    ptr_stats->temp_rel_occupancy_percent = 50.0f;
    ptr_stats->temp_queue_length = 1;
    ptr_stats->temp_free_spots = 10;
    ptr_stats->temp_time_left = 5;
    ptr_file = tmpfile();
    assert(save_temp_dataset(ptr_stats, ptr_file) == 1);
    rewind(ptr_file);
    char buf[128];
    assert(fgets(buf, sizeof(buf), ptr_file) != NULL);
    fclose(ptr_file);
    free(ptr_stats);
    ptr_stats = NULL; 
    ptr_file = NULL;
    printf("OK\n");

    return 0;
}
