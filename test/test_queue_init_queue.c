/**
 * @file test_queue_init_queue.c
 * @brief Unit tests for the init_queue() function, covering successful
 *        allocation, zero-initialization of all fields, and pointer independence.
 */

#include <assert.h>
#include <stdio.h>

#include "../include/queue.h"

int main() {
    Queue *ptr_queue1 = NULL;
    Queue *ptr_queue2 = NULL;

    // Test 1: Return value is not NULL
    printf("Test 1: init_queue()                   → returns valid queue:  ");
    ptr_queue1 = init_queue();
    assert(ptr_queue1 != NULL);
    free_queue(ptr_queue1);
    ptr_queue1 = NULL;
    printf("OK\n");

    // Test 2: All fields are zero/null-initialized
    printf("Test 2: init_queue()                   → fields initialized:  ");
    ptr_queue1 = init_queue();
    assert(ptr_queue1 != NULL);
    assert(ptr_queue1->ptr_head == NULL);
    assert(ptr_queue1->ptr_tail == NULL);
    assert(ptr_queue1->size == 0);

    free_queue(ptr_queue1);
    ptr_queue1 = NULL;
    printf("OK\n");

    // Test 3: Two calls return independent pointers
    printf("Test 3: init_queue() called twice      → different pointers:  ");
    ptr_queue1  = init_queue();
    ptr_queue2 = init_queue();
    assert(ptr_queue1  != NULL);
    assert(ptr_queue2 != NULL);
    assert(ptr_queue1  != ptr_queue2);
    free_queue(ptr_queue1);
    free_queue(ptr_queue2);
    ptr_queue1  = NULL;
    ptr_queue2 = NULL;
    printf("OK\n");

    return 0;
}