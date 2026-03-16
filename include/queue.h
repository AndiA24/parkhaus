/**
 * @file queue.h
 * @brief Vehicle waiting queue structure and interface.
 *
 * Declares the QueueNode and Queue structs as well as functions for
 * initialising, enqueuing, dequeuing, and freeing the waiting queue.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "vehicle.h"

typedef struct SimStats SimStats;

/**
 * @brief A node in the singly-linked waiting queue.
 */
typedef struct QueueNode {
    Vehicle             *ptr_vehicle;   /**< Pointer to the vehicle held by this node. */
    struct QueueNode    *ptr_next;     /**< Pointer to the next node in the queue, or NULL if this is the tail. */
} QueueNode;

/**
 * @brief A singly-linked FIFO queue of waiting vehicles.
 */
typedef struct Queue{
    QueueNode *ptr_head; /**< Pointer to the first node in the queue, or NULL if empty. */
    QueueNode *ptr_tail; /**< Pointer to the last node in the queue, or NULL if empty. */
    int        size;     /**< Current number of nodes (vehicles) in the queue. */
} Queue;

/**
 * @brief Initializes an empty queue.
 *
 * Sets all fields of the Queue structure to their initial values
 * (head and tail to NULL, size to 0).
 *
 *  @return Pointer of the initialized queue 
 */
Queue *init_queue();

/**
 * @brief Adds a vehicle to the end of the waiting queue.
 *
 * Creates a new QueueNode for the given vehicle and appends it
 * to the tail of the queue. Increments size by 1.
 *
 * @param[in,out] ptr_queue   Pointer to the waiting queue
 * @param[in]     vehicle Pointer to the vehicle to be enqueued
 * 
 * @return 1 on success, -1 if any param is NULL
 */
int enqueue(Queue *ptr_queue, Vehicle *ptr_vehicle);

/**
 * @brief Removes and returns the first vehicle from the waiting queue.
 *
 * Removes the node at the head of the queue, decrements size by 1,
 * and returns the pointer to the vehicle it contained.
 * Returns NULL if the queue is empty.
 *
 * @param[in,out] ptr_queue Pointer to the waiting queue
 * @param[in,out] ptr_stats Pointer to the simulation stats
 *
 * @return Pointer to the next vehicle allowed to enter the parking lot,
 *         or NULL if the queue is empty / if any param is NULL
 */
Vehicle *dequeue(Queue *ptr_queue, SimStats *ptr_stats);

/**
 * @brief Increments the queue time of all vehicles in the waiting queue at each time step.
 *
 * Iterates through all nodes in the queue and increases the queue_time
 * of each contained vehicle by one. 
 * Does nothing if the queue is empty.
 *
 * @param[in,out] ptr_queue Pointer to the waiting queue
 * 
 * @return 1 on success, -1 if ptr_queue is NULL
 */
int increment_queue_time(Queue *ptr_queue);

/**
 * @brief Frees all resources associated with the queue.
 *
 * Traverses all remaining nodes in the queue and releases their
 * allocated memory. 
 * The queue itself is reset to its initial state, size is reset to 0.
 * The contained Vehicle objects are also freed.
 *
 * @param[in,out] ptr_queue Pointer to the queue to be deleted
 * @param[in,out] ptr_stats Pointer to the stats to have the data from the vehicles safed inside of
 * 
 * @return 1 on success, -1 if any param is NULL
 */
int delete_queue(Queue *ptr_queue, SimStats *ptr_stats);

/**
 * @brief Frees all dynamically allocated memory associated with the Queue structure.
 *
 * Frees the Queue structure that was allocated by init_queue
 *
 * @param[in] ptr_queue Pointer to the Queue structure to be freed.
 * 
 * @return 1 on success, -1 if ptr_queue is NULL
 */
int free_queue(Queue *ptr_queue);

#endif