/**
 * @file test_stats_create_output_file.c
 * @brief Unit tests for the create_output_file() function, covering NULL Gurads
 *        and successful file creation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/stats.h"
#include "../include/config.h"

static SimConfig *create_test_config(const char *filename) {
    SimConfig *ptr_config = calloc(1, sizeof(*ptr_config));
    strncpy(ptr_config->output_file_name, filename, sizeof(ptr_config->output_file_name) - 1);
    return ptr_config;
}


int main() {
    SimConfig *ptr_config = NULL;
    FILE *ptr_file = NULL;

    // Test 1: NULL Guard
    printf("Test 1: NULL Guard: ");
    assert(create_output_file(NULL) == NULL);
    printf("OK\n");

    // Test 2: Valid config — file is created and FILE* is returned
    //
    // Expected values after call:
    //   return value != NULL (File Pointer)
    //   file exists on disk
    printf("Test 2: Valid config creates file: ");
    ptr_config = create_test_config("test_tmp_output.csv");
    remove(ptr_config->output_file_name);
    ptr_file = create_output_file(ptr_config);
    assert(ptr_file != NULL);
    fclose(ptr_file);
    remove(ptr_config->output_file_name);
    free(ptr_config);
    ptr_config = NULL; ptr_file = NULL;
    printf("OK\n");

    return 0;
}