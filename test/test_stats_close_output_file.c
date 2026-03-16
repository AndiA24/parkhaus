/**
 * @file test_stats_close_output_file.c
 * @brief Unit tests close_output_file() function, covering NULL Guard,
 *        and successful file closing.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/stats.h"


int main() {
    FILE *ptr_file = NULL;

    // Test 1: NULL Guard
    printf("Test 1: Checking NULL Guard: ");
    assert(close_output_file(NULL) == -1);
    printf("OK\n");

    // Test 2: Open OUtput-file is closed successfully
    //
    // Expected values after call:
    //   return value = 1
    printf("Test 2: Open Output-file is closed: ");
    ptr_file = tmpfile();
    assert(ptr_file != NULL);
    assert(close_output_file(ptr_file) == 0);
    ptr_file = NULL;
    printf("OK\n");

    return 0;
}
