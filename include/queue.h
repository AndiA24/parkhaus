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

void init_queue(Queue *queue){}

void enqueue(Queue *queue, Vehicle *vehicle){}

Vehicle *dequeue(Queue *queue){}

void delete_queue(Queue *queue){}