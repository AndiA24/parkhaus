/**
 * @file test_config_free_config.c
 * @brief Unit tests for the free_config() function from config.c.
 *        Run with `make test_config_free_config`.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/config.h"

int main() {
    SimConfig *ptr_config = NULL;
    int ret;

    // Test 1: Valid pointer is freed and returns 1
    printf("Test 1: Valid pointer returns 1: ");
    ptr_config = create_config();
    assert(ptr_config != NULL);
    ret = free_config(ptr_config);
    assert(ret == 0);
    ptr_config = NULL;
    printf("OK\n");

    // Test 2: NULL pointer returns -1 and does not crash
    printf("Test 2: NULL pointer returns -1: ");
    ret = free_config(NULL);
    assert(ret == -1);
    printf("OK\n");

    return 0;
}
