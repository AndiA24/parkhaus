/**
 * @file test_queue_delete_queue.c
 * @brief Unit tests for the delete_queue() function.
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
    Queue *ptr_queue   = NULL;
    Vehicle *ptr_vehicle1 = NULL;
    Vehicle *ptr_vehicle2 = NULL;
    SimStats *ptr_stats = NULL;

    // Test 1: both Args are NULL
    printf("Test 1: delete_queue(NULL, NULL)           → returns -1:  ");
    assert(delete_queue(NULL, NULL) == -1);
    printf("OK\n");

    // Test 2: stats pointer is NULL
    printf("Test 2: delete_queue(valid queue, NULL)    → returns -1:  ");
    ptr_queue = init_queue();
    assert(delete_queue(ptr_queue, NULL) == -1);
    free_queue(ptr_queue);
    ptr_queue = NULL;
    printf("OK\n");

    // Test 3: queue pointer is NULL
    printf("Test 3: delete_queue(NULL, valid stats)    → returns -1:  ");
    ptr_stats = create_test_stats();
    assert(delete_queue(NULL, ptr_stats) == -1);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    // Test 4: pointers are valid
    printf("Test 4: delete_queue(empty queue, stats)   → returns  1:  ");
    ptr_queue = init_queue();
    ptr_stats = create_test_stats();
    assert(delete_queue(ptr_queue, ptr_stats) == 0);
    free(ptr_stats);
    ptr_queue = NULL;
    ptr_stats = NULL;
    printf("OK\n");

    // Test 5: delete queue with multiple vehicles
    printf("Test 5: delete_queue(2 vehicles, stats)    → returns  1:  ");
    ptr_queue = init_queue();
    ptr_stats = create_test_stats();
    ptr_vehicle1 = create_test_vehicle();
    ptr_vehicle2 = create_test_vehicle();
    enqueue(ptr_queue, ptr_vehicle1, ptr_stats);
    enqueue(ptr_queue, ptr_vehicle2, ptr_stats);
    assert(delete_queue(ptr_queue, ptr_stats) == 0);
    free(ptr_stats);   
    printf("OK\n");

    return 0;
}