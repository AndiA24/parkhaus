/**
 * @file test_queue_init_queue.c
 * @brief Unit tests for the init_queue() function, covering successful
 *        allocation, zero-initialization of all fields, and pointer independence.
 *        Run with `make test_queue_init_queue`.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"

int main() {
    Queue *ptr_queue = NULL;
    Queue *ptr_queue2 = NULL;

    // Test 1: Return value is not NULL
    printf("Test 1: Return value is not NULL: ");
    ptr_queue = init_queue();
    assert(ptr_queue != NULL);
    free_queue(ptr_queue); // darf schon verwendet werden?
    ptr_queue = NULL;
    printf("OK\n");

    // Test 2: All fields are zero/null-initialized
    printf("Test 2: All fields are zero after init: ");
    ptr_queue = init_queue();
    assert(ptr_queue != NULL);
    assert(ptr_queue->ptr_head == NULL);
    assert(ptr_queue->ptr_tail == NULL);
    assert(ptr_queue->size == 0);

    free_queue(ptr_queue);
    ptr_queue = NULL;
    printf("OK\n");

    // Test 3: Two calls return independent pointers
    printf("Test 3: Two calls return different pointers: ");
    ptr_queue  = init_queue();
    ptr_queue2 = init_queue();
    assert(ptr_queue  != NULL);
    assert(ptr_queue2 != NULL);
    assert(ptr_queue  != ptr_queue2);
    free_queue(ptr_queue);
    free_queue(ptr_queue2);
    ptr_queue  = NULL;
    ptr_queue2 = NULL;
    printf("OK\n");

    return 0;
}