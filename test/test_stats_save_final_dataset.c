/**
 * @file test_stats_save_final_dataset.c
 * @brief Unit tests for the save_final_dataset() function, covering NULL Guards
 *        and successful saving of final simulation statistics to file.
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
    assert(save_final_dataset(NULL, NULL) == -1);
    assert(save_final_dataset(NULL, ptr_file) == -1);
    assert(save_final_dataset(ptr_stats, NULL) == -1);
    fclose(ptr_file);
    free(ptr_stats);
    ptr_stats = NULL; 
    ptr_file = NULL;
    printf("OK\n");

    // Test 2: Valid Arguments
    //
    // Expected values after call:
    //   return value = 1
    //   file contains header line and one data line
    printf("Test 2: Valid call writes to file: ");
    ptr_stats = create_test_stats();
    ptr_stats->total_exits = 10;
    ptr_stats->total_entries = 12;
    ptr_stats->peak_rel_occupancy = 75.0f;
    ptr_file = tmpfile();
    assert(save_final_dataset(ptr_stats, ptr_file) == 1);
    rewind(ptr_file);
    char buf[256];
    assert(fgets(buf, sizeof(buf), ptr_file) != NULL);  // header line
    assert(fgets(buf, sizeof(buf), ptr_file) != NULL);  // data line
    fclose(ptr_file);
    free(ptr_stats);
    ptr_stats = NULL; 
    ptr_file = NULL;
    printf("OK\n");

    return 0;
}
