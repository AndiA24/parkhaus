/**
 * @file test_queue_free_queue.c
 * @brief Unit tests for the free_queue() function.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"

int main() {
    Queue *ptr_queue = NULL;

    // Test 1: queue pointer is NULL
    printf("Test 1: free_queue(NULL)          → returns -1:  ");
    assert(free_queue(NULL) == -1);
    printf("OK\n");

    // Test 2: valid empty queue
    printf("Test 2: free_queue(empty queue)   → returns  1:  ");
    ptr_queue = init_queue();
    assert(free_queue(ptr_queue) == 0);
    ptr_queue = NULL;
    printf("OK\n");

    return 0;
}