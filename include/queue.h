#include "vehicle.h"

typedef struct QueueNode {
    Vehicle          *vehicle;
    struct QueueNode        *previous;
    struct QueueNode        *next;
} QueueNode;

typedef struct {
    QueueNode *head;
    QueueNode *tail;
    int        size;
} Queue;

/**
 * @brief Initializes an empty queue.
 *
 * Sets all fields of the Queue structure to their initial values
 * (head and tail to NULL, size to 0).
 *
 * @param[out] queue Pointer to the queue to be initialized
 */
void init_queue(Queue *queue){}

/**
 * @brief Adds a vehicle to the end of the waiting queue.
 *
 * Creates a new QueueNode for the given vehicle and appends it
 * to the tail of the queue. Increments size by 1.
 *
 * @param[in,out] queue   Pointer to the waiting queue
 * @param[in]     vehicle Pointer to the vehicle to be enqueued
 */
void enqueue(Queue *queue, Vehicle *vehicle){}

/**
 * @brief Removes and returns the first vehicle from the waiting queue.
 *
 * Removes the node at the head of the queue, decrements size by 1,
 * and returns the pointer to the vehicle it contained.
 * Returns NULL if the queue is empty.
 *
 * @param[in,out] queue Pointer to the waiting queue
 *
 * @return Pointer to the next vehicle allowed to enter the parking lot,
 *         or NULL if the queue is empty
 */
Vehicle *dequeue(Queue *queue){}

/**
 * @brief Frees all resources associated with the queue.
 *
 * Traverses all remaining nodes in the queue and releases their
 * allocated memory. 
 * The queue itself is reset to its initial state, size is reset to 0.
 * The contained Vehicle objects are not freed.
 *
 * @param[in,out] queue Pointer to the queue to be deleted
 */
void delete_queue(Queue *queue){}