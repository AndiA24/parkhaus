/**
 * @file test_queue_dequeue.c
 * @brief Unit tests for the dequeue() function.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/stats.h"

Vehicle *create_test_vehicle(){
    Vehicle *ptr_vehicle = calloc(1, sizeof *ptr_vehicle); 
    return ptr_vehicle;
}

SimStats *create_test_stats(){
    SimStats *ptr_stats = calloc(1, sizeof *ptr_stats);
    return ptr_stats;
}

int main() {
    Queue *ptr_queue = NULL;
    SimStats *ptr_stats = NULL;
    Vehicle *ptr_vehicle = NULL;
    Vehicle *ptr_result = NULL;

    // Test 1: both Args are NULL
    printf("Test 1: dequeue(NULL, NULL)           → returns NULL:  ");
    assert(dequeue(NULL, NULL) == NULL);
    printf("OK\n");

    // Test 2: stats pointer is NULL
    printf("Test 2: dequeue(valid queue, NULL)    → returns NULL:  ");
    ptr_queue = init_queue();
    assert(dequeue(ptr_queue, NULL) == NULL);
    free_queue(ptr_queue);
    ptr_queue = NULL;
    printf("OK\n");

    // Test 3: queue pointer is NULL
    printf("Test 3: dequeue(NULL, valid stats)    → returns NULL:  ");
    ptr_stats = create_test_stats();
    assert(dequeue(NULL, ptr_stats) == NULL);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    // Test 4: queue head is NULL
    printf("Test 4: dequeue(empty queue, stats)   → returns NULL:  ");
    ptr_queue = init_queue();
    ptr_stats = create_test_stats();
    assert(dequeue(ptr_queue, ptr_stats) == NULL);
    free_queue(ptr_queue);
    free(ptr_stats);
    printf("OK\n");

    // Test 5: dequeue one vehicle
    printf("Test 5: dequeue(one vehicle, stats)   → returns dequeued vehicle:  ");
    ptr_queue = init_queue();
    ptr_vehicle = create_test_vehicle();
    ptr_stats = create_test_stats();

    enqueue(ptr_queue, ptr_vehicle, ptr_stats);
    ptr_result = dequeue(ptr_queue, ptr_stats);

    assert(ptr_result == ptr_vehicle);
    assert(ptr_queue->size == 0);
    assert(ptr_queue->ptr_head == NULL);
    assert(ptr_queue->ptr_tail == NULL);

    free(ptr_vehicle); 
    free_queue(ptr_queue);
    free(ptr_stats);  
    printf("OK\n");

    // Test 6: stats updated after dequeue
    printf("Test 6: dequeue(one vehicle, stats)   → updates stats correctly:  ");
    ptr_queue = init_queue();
    ptr_vehicle = create_test_vehicle();
    ptr_stats = create_test_stats();
    ptr_stats->step_num = 2;
    enqueue(ptr_queue, ptr_vehicle, ptr_stats);
    ptr_stats->step_num = 4;
    ptr_result = dequeue(ptr_queue, ptr_stats);
    assert(ptr_stats->total_queue_time == 2);
    assert(ptr_stats->total_queued == 1);

    free(ptr_result);
    free_queue(ptr_queue);
    free(ptr_stats);
    printf("OK\n");

    return 0;
}