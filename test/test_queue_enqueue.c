/**
 * @file test_queue_enqueue.c
 * @brief Unit tests for the enqueue() function.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/stats.h"

Vehicle *test_vehicle(){
    Vehicle *ptr_vehicle = calloc(1, sizeof *ptr_vehicle); 
    return ptr_vehicle;
}

SimStats *test_stats(){
    SimStats *ptr_stats = calloc(1, sizeof *ptr_stats);
    return ptr_stats;
}

int main() {
    Queue   *ptr_queue   = NULL;
    Vehicle *ptr_vehicle1 = NULL;
    Vehicle *ptr_vehicle2 = NULL;
    Vehicle *ptr_vehicle3 = NULL;
    SimStats *ptr_stats = test_stats();

    // Test 1: Both Args are NULL
    printf("Test 1: enqueue(NULL, NULL)           → returns -1:  ");
    assert(enqueue(NULL, NULL) == -1);
    printf("OK\n");

    // Test 2: vehicle pointer is NULL
    printf("Test 2: enqueue(valid queue, NULL)    → returns -1:  ");
    ptr_queue = init_queue();
    assert(enqueue(ptr_queue, NULL) == -1);
    delete_queue(ptr_queue, ptr_stats);
    ptr_queue = NULL;
    printf("OK\n");

    // Test 3: queue pointer is NULL
    printf("Test 3: enqueue(NULL, valid vehicle)  → returns -1:  ");
    ptr_vehicle1 = test_vehicle();
    assert(enqueue(NULL, ptr_vehicle1) == -1);
    free(ptr_vehicle1);
    ptr_vehicle1 = NULL;
    printf("OK\n");


    // Test 4: Enqueue one element
    printf("Test 4: enqueue(queue, one vehicle)   → size=1, head==tail:   ");
    ptr_queue    = init_queue();
    ptr_vehicle1 = test_vehicle();

    assert(enqueue(ptr_queue, ptr_vehicle1) == 1);

    assert(ptr_queue->size == 1);
    assert(ptr_queue->ptr_head != NULL);
    assert(ptr_queue->ptr_tail != NULL);
    assert(ptr_queue->ptr_head == ptr_queue->ptr_tail);
    assert(ptr_queue->ptr_head->ptr_vehicle == ptr_vehicle1);   
    assert(ptr_queue->ptr_head->ptr_next == NULL);              

    delete_queue(ptr_queue, ptr_stats);
    ptr_queue    = NULL;
    ptr_vehicle1 = NULL;
    printf("OK\n");

    // Test 5: Enqueue two elements
    printf("Test 5: enqueue(queue, 2x vehicles)   → FIFO order maintained:   ");
    ptr_queue    = init_queue();
    ptr_vehicle1 = test_vehicle();
    ptr_vehicle2 = test_vehicle();

    assert(enqueue(ptr_queue, ptr_vehicle1) == 1);
    assert(enqueue(ptr_queue, ptr_vehicle2) == 1);

    assert(ptr_queue->size == 2);
    assert(ptr_queue->ptr_head != ptr_queue->ptr_tail);        
    assert(ptr_queue->ptr_head->ptr_vehicle == ptr_vehicle1);  
    assert(ptr_queue->ptr_tail->ptr_vehicle == ptr_vehicle2);   
    assert(ptr_queue->ptr_head->ptr_next == ptr_queue->ptr_tail); 
    assert(ptr_queue->ptr_tail->ptr_next == NULL);              

    delete_queue(ptr_queue, ptr_stats);
    ptr_queue    = NULL;
    ptr_vehicle1 = NULL;
    ptr_vehicle2 = NULL;
    printf("OK\n");

    // Test 6: Enqueue three elements
    printf("Test 6: enqueue(queue, 3x vehicles)   → tail updated correctly:   ");
    ptr_queue    = init_queue();
    ptr_vehicle1 = test_vehicle();
    ptr_vehicle2 = test_vehicle();
    ptr_vehicle3 = test_vehicle();

    assert(enqueue(ptr_queue, ptr_vehicle1) == 1);
    assert(enqueue(ptr_queue, ptr_vehicle2) == 1);
    assert(enqueue(ptr_queue, ptr_vehicle3) == 1);

    assert(ptr_queue->size == 3);
    assert(ptr_queue->ptr_head->ptr_vehicle == ptr_vehicle1);
    assert(ptr_queue->ptr_head->ptr_next->ptr_vehicle == ptr_vehicle2);   
    assert(ptr_queue->ptr_tail->ptr_vehicle == ptr_vehicle3);   
    assert(ptr_queue->ptr_tail->ptr_next == NULL);              

    delete_queue(ptr_queue, ptr_stats);
    ptr_queue    = NULL;
    ptr_vehicle1 = NULL;
    ptr_vehicle2 = NULL;
    ptr_vehicle3 = NULL;
    printf("OK\n");

    free(ptr_stats);
    ptr_stats = NULL;

    return 0;
}