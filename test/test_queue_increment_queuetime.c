/**
 * @file test_queue_increment_queuetime.c
 * @brief Unit tests for the increment_queue_time() function.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"
#include "../include/vehicle.h"

Vehicle *create_test_vehicle(){
    Vehicle *ptr_vehicle = calloc(1, sizeof *ptr_vehicle); 
    return ptr_vehicle;
}

int main() {
    Queue *ptr_queue = NULL;
    Vehicle *ptr_vehicle1 = NULL;
    Vehicle *ptr_vehicle2 = NULL;

    // Test 1: queue pointer is NULL
    printf("Test 1: increment_queue_time(NULL)        → returns -1:  ");
    assert(increment_queue_time(ptr_queue) == -1);
    printf("OK \n");

    // Test 2: increment queue time one vehicle
    printf("Test 2: one vehicle, 1x increment         → queue_time +1:  ");
    ptr_queue = init_queue();
    ptr_vehicle1 = create_test_vehicle();
    enqueue(ptr_queue, ptr_vehicle1);
    assert(increment_queue_time(ptr_queue) == 1);
    assert(ptr_vehicle1->queue_time == 1);
    free_queue(ptr_queue);
    free(ptr_vehicle1);
    printf("OK \n");

    // Test 3: increment queue time multiple vehicles
    printf("Test 3: two vehicles, 1x increment        → queue_time +1:  ");
    ptr_queue = init_queue();
    ptr_vehicle1 = create_test_vehicle();
    ptr_vehicle2 = create_test_vehicle();
    enqueue(ptr_queue, ptr_vehicle1);
    enqueue(ptr_queue, ptr_vehicle2);
    assert(increment_queue_time(ptr_queue) == 1);
    assert(ptr_vehicle1->queue_time == 1);
    assert(ptr_vehicle2->queue_time == 1);
    free_queue(ptr_queue);
    free(ptr_vehicle1);
    free(ptr_vehicle2);
    printf("OK \n");

    // Test 4: double increment queue time one vehicle
    printf("Test 4: one vehicle, 2x increment         → queue_time +2:  ");
    ptr_queue = init_queue();
    ptr_vehicle1 = create_test_vehicle();
    enqueue(ptr_queue, ptr_vehicle1);
    assert(increment_queue_time(ptr_queue) == 1);
    assert(increment_queue_time(ptr_queue) == 1);
    assert(ptr_vehicle1->queue_time == 2);
    free_queue(ptr_queue);
    free(ptr_vehicle1);
    printf("OK \n");

    return 0;
}

