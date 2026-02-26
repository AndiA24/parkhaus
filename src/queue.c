#include "../include/queue.h"
#include "../include/vehicle.h"

/* 
FUNCTION init_queue(ptr_queue : Queue*)
    ptr_queue->ptr_head = NULL                                  // initialize head to NULL
    ptr_queue->ptr_tail = NULL                                  // initialize tail to NULL
    ptr_queue->size = 0                                         // set size to 0
ENDFUNCTION
*/

/*
FUNCTION enqueue(ptr_queue : Queue*, ptr_vehicle : Vehicle*)
    ptr_new_node : QueueNode*                                   // temporary pointer for new node
    ptr_new_node = malloc(sizeof *ptr_new_node)                 // allocate memory for new node

    IF !ptr_new_node THEN
        RETURN ERROR                                            // return error if allocation fails
    ENDIF
    
    ptr_new_node->ptr_vehicle  = ptr_vehicle;                   // stores vehicle in node      
    ptr_new_node->ptr_next     = NULL;                          // new node at end -> no next

    IF ptr_queue->ptr_tail == NULL THEN
        ptr_queue->ptr_head = ptr_new_node                      // queue was empty → head points to new node
    ELSE
        ptr_queue->ptr_tail->ptr_next = ptr_new_node            // link previous tail to new node
    ENDIF
    
    ptr_queue->ptr_tail = ptr_new_node                          // update tail to new node
    ptr_queue->size = ptr_queue->size +1                        // increment queue size
ENDFUNCTION
*/

/*
FUNCTION dequeue(ptr_queue : Queue*) RETURNS Vehicle*
    IF ptr_queue->ptr_head == NULL THEN
        RETURN NULL                                             // queue is empty, nothing to dequeue
    ENDIF
    
    ptr_prev_head : QueueNode*
    ptr_prev_head = ptr_queue->ptr_head                         // pointer to current head node
    ptr_vehicle : Vehicle*
    ptr_vehicle = ptr_prev_head->ptr_vehicle                    // store vehicle to return

    ptr_queue->ptr_head = ptr_prev_head->ptr_next               // move head to next node

    IF ptr_queue->ptr_head == NULL THEN
        ptr_queue->ptr_tail = NULL                              // queue is empty -> tail NULL
    ENDIF

    free(ptr_prev_head)                                         // free memory of previous head node
    ptr_queue->size = ptr_queue->size -1                        // decrement queue size

    RETURN ptr_vehicle                                          // return dequeued vehicle
ENDFUNCTION
*/

/*
FUNCTION delete_queue(ptr_queue : Queue*)
    WHILE ptr_queue->ptr_head != NULL
        ptr_vehicle : Vehicle*
        ptr_vehicle = dequeue(ptr_queue)                        // dequeue each node until queue is empty
        free(ptr_vehicle)                                       // free vehicle memory
    ENDWHILE
ENDFUNCTION
*/