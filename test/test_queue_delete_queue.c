/**
 * @file test_queue_increment_queuetime.c
 * @brief Unit tests for the increment_queue_time() function.
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
    Queue   *ptr_queue   = NULL;
    Vehicle *ptr_vehicle = NULL;
    SimStats *ptr_stats = NULL;

    // Test 1: Both Args are NULL
    printf("Test 1: Both Args are NULL:  ");
    assert(delete_queue(NULL, NULL) == -1);
    printf("OK\n");

    // Test 2: stats pointer is NULL
    printf("Test 2: stats pointer is NULL:  ");
    ptr_queue = init_queue();
    assert(delete_queue(ptr_queue, NULL) == -1);
    free_queue(ptr_queue);
    ptr_queue = NULL;
    printf("OK\n");

    // Test 3: queue pointer is NULL
    printf("Test 3: queue pointer is NULL:  ");
    ptr_stats = create_test_stats();
    assert(delete_queue(NULL, ptr_stats) == -1);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n");

    // Test 4: pointers are valid
    printf("Test 4: Both args are valid:  ");
    ptr_queue = init_queue();
    ptr_stats = create_test_stats();
    assert(delete_queue(ptr_queue, ptr_stats) == 1);
    free(ptr_stats);
    ptr_queue = NULL;
    ptr_stats = NULL;
    printf("OK\n");


}