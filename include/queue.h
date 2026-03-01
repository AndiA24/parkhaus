#include "vehicle.h"

/**
 * @brief A node in the doubled-linked waiting queue.
 */
typedef struct QueueNode {
    Vehicle             *ptr_vehicle;   /**< Pointer to the vehicle held by this node. */
    struct QueueNode    *ptr_previous; /**< Pointer to the previous node in the queue, or NULL if this is the head. */
    struct QueueNode    *ptr_next;     /**< Pointer to the next node in the queue, or NULL if this is the tail. */
} QueueNode;

/**
 * @brief A doubled-linked FIFO queue of waiting vehicles.
 */
typedef struct {
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
 * @param[out] queue Pointer to the queue to be initialized
 */
void init_queue(Queue *ptr_queue);

/**
 * @brief Adds a vehicle to the end of the waiting queue.
 *
 * Creates a new QueueNode for the given vehicle and appends it
 * to the tail of the queue. Increments size by 1.
 *
 * @param[in,out] queue   Pointer to the waiting queue
 * @param[in]     vehicle Pointer to the vehicle to be enqueued
 */
void enqueue(Queue *ptr_queue, Vehicle *ptr_vehicle);

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
Vehicle *dequeue(Queue *ptr_queue);

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
void delete_queue(Queue *ptr_queue);