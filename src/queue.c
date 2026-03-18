/**
 * @file queue.c
 * @brief Vehicle waiting queue management.
 *
 * Provides functions to initialise, enqueue, dequeue, and free the
 * waiting queue after simulation end.
 */

#include <stdlib.h>
#include <stdio.h>

#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/stats.h"
#include "../include/utils.h"

Queue *init_queue()
{
    Queue *ptr_queue = malloc(sizeof *ptr_queue);               // allocate memory for queue

    if (ptr_queue == NULL)
    {
        return NULL;
    }

    ptr_queue->ptr_head = NULL;
    ptr_queue->ptr_tail = NULL;
    ptr_queue->size = 0;

    return ptr_queue;                                           // return initialized queue                                              
}

int enqueue(Queue *ptr_queue, Vehicle *ptr_vehicle, SimStats *ptr_stats)
{
    if (ptr_queue == NULL || ptr_vehicle == NULL || ptr_stats == NULL) {
        output(2, "Error: Failed to enqueue vehicle. Invalid argument.\n", 2, 0, NULL);
        return -1;
    }

    QueueNode *ptr_new_node = malloc(sizeof *ptr_new_node);     // allocate memory for new node
    if (ptr_new_node == NULL) {
        output(2, "Error: Failed to allocate memory for new node.\n", 2, 0, NULL);
        return -1;
    }
    
    ptr_new_node->ptr_vehicle = ptr_vehicle;                    // store vehicle in node
    ptr_new_node->ptr_next = NULL;
    ptr_new_node->ptr_vehicle->queue_time = ptr_stats->step_num;

    if (ptr_queue->ptr_tail == NULL) {                           // check if queue empty
        ptr_queue->ptr_head = ptr_new_node;                     // head point to new node
    } 
    else {
        ptr_queue->ptr_tail->ptr_next = ptr_new_node;           // link previous tail to new node
    }

    ptr_queue->ptr_tail = ptr_new_node;                         // update tail to new node
    ptr_queue->size++;                                          // increment queue size
    return 0;
}

Vehicle *dequeue(Queue *ptr_queue, SimStats *ptr_stats) 
{
    if (ptr_queue == NULL || ptr_stats == NULL) {
        output(2, "Error: Failed to dequeue vehicle. Invalid argument.\n", 2, 0, NULL);
        return NULL;
    }
    if (ptr_queue->ptr_head == NULL) {
        return NULL;
    }

    QueueNode *ptr_prev_head = ptr_queue->ptr_head;             // temp pointer to current head node
    Vehicle *ptr_vehicle = ptr_prev_head->ptr_vehicle;          // store vehicle to return

    ptr_stats->total_queue_time += (ptr_stats->step_num - ptr_vehicle->queue_time);  // update total queue time

    ptr_queue->ptr_head = ptr_prev_head->ptr_next;              // set head pointer to next node

    if (ptr_queue->ptr_head == NULL) {
        ptr_queue->ptr_tail = NULL;
    }

    free(ptr_prev_head);                                        // free memory of previous head node
    ptr_queue->size--;                                          // decrement queue size 

    if ((ptr_stats->step_num - ptr_vehicle->queue_time) > 0) {  // check if vehicle was queued
        ptr_stats->total_queued++;                              // increment total queued
    }
    
    return ptr_vehicle;                                         // return dequeued vehicle
}

int delete_queue(Queue *ptr_queue, SimStats *ptr_simstats) 
{
    if (ptr_queue == NULL || ptr_simstats == NULL) {
        output(2, "Error: Failed to delete queue. Invalid argument.\n", 2, 0, NULL);
        return -1;
    }

    while (ptr_queue->ptr_head != NULL) {
        Vehicle *ptr_vehicle = dequeue(ptr_queue, ptr_simstats); // dequeue each node until queue is empty
        if (ptr_vehicle != NULL) {
            free_vehicle(ptr_vehicle);                          // free vehicle memory                                                            
        }                           
    }

    free_queue(ptr_queue);
    return 0;
}

int free_queue(Queue *ptr_queue) 
{
    if (ptr_queue == NULL) {
        output(2, "Error: Failed to free memory allocated for queue. Invalid argument.\n", 2, 0, NULL);
        return -1;
    }
    free(ptr_queue);                                            // free queue memory
    return 0;
}

/* 
PSEUDOCODE

FUNCTION init_queue()
    ptr_queue : Queue*
    IF ptr_queue<- CALL malloc(CALL sizeof(*ptr_queue)) != 1 THEN
        RETURN
    END IF
    ptr_queue->ptr_head = NULL                                  // initialize head to NULL
    ptr_queue->ptr_tail = NULL                                  // initialize tail to NULL
    ptr_queue->size = 0                                         // set size to 0
    RETURN ptr_queue
END FUNCTION
*/

/*
FUNCTION enqueue(ptr_queue : Queue*, ptr_vehicle : Vehicle*)
    ptr_new_node : QueueNode*                                   // temporary pointer for new node
    ptr_new_node = CALL malloc(CALL sizeof *ptr_new_node)            // allocate memory for new node

    IF !ptr_new_node THEN
        RETURN ERROR                                            // return error if allocation fails
    ENDIF
    
    ptr_new_node->ptr_vehicle  = ptr_vehicle;                   // stores vehicle in node      
    ptr_new_node->ptr_next     = NULL;                          // new node at end -> no next

    IF ptr_queue->ptr_tail == NULL THEN
        ptr_queue->ptr_head = ptr_new_node                      // queue was empty -> head points to new node
    ELSE
        ptr_queue->ptr_tail->ptr_next = ptr_new_node            // link previous tail to new node
    ENDIF
    
    ptr_queue->ptr_tail = ptr_new_node                          // update tail to new node
    ptr_queue->size = ptr_queue->size +1                        // increment queue size
END FUNCTION
*/

/*
FUNCTION dequeue(ptr_queue : Queue*, ptr_simstats : SimStats*) RETURNS Vehicle*
    IF ptr_queue->ptr_head == NULL THEN
        RETURN NULL                                             // queue is empty, nothing to dequeue
    ENDIF
    
    ptr_prev_head : QueueNode*
    ptr_prev_head = ptr_queue->ptr_head                         // pointer to current head node
    ptr_vehicle : Vehicle*
    ptr_vehicle = ptr_prev_head->ptr_vehicle                    // store vehicle to return

    ptr_simstats->total_queue_time += ptr_vehicle->queue_time   // add dequeued vehicle’s queue time to total queue time

    ptr_queue->ptr_head = ptr_prev_head->ptr_next               // move head to next node

    IF ptr_queue->ptr_head == NULL THEN
        ptr_queue->ptr_tail = NULL                              // queue is empty -> tail NULL
    ENDIF

    CALL free(ptr_prev_head)                                    // free memory of previous head node
    ptr_queue->size = ptr_queue->size -1                        // decrement queue size
    IF ptr_vehicle->queue_time > 0
        ptr_simstats->total_queued++
    END IF
    
    RETURN ptr_vehicle                                          // return dequeued vehicle
END FUNCTION
*/

/* 
FUNCTION increment_queue_time(ptr_queue : Queue*)      
    ptr_temp_node : QueueNode*          
    ptr_temp_node = ptr_queue->ptr_head                         // temporary pointer
    
    WHILE ptr_temp_node != NULL                                 // iterate through all queue nodes
        ptr_temp_node->ptr_vehicle->queue_time++                // increment queue time
        ptr_temp_node = ptr_temp_node->ptr_next                 // move to next node in queue
    ENDWHILE
END FUNCTION
*/ 

/*
FUNCTION delete_queue(ptr_queue : Queue*, ptr_stats : SimStats*)
    WHILE ptr_queue->ptr_head != NULL
        ptr_vehicle : Vehicle*
        ptr_vehicle = CALL dequeue(ptr_queue, ptr_stats)                    // dequeue each node until queue is empty
        CALL free_vehicle(ptr_vehicle)                                      // free vehicle memory
    ENDWHILE
END FUNCTION
*/

/*
FUNCTION free_queue(ptr_queue : Queue*)
    CALL free(ptr_queue)
END FUNCTION
*/