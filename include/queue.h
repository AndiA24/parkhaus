#include "vehicle.h"

typedef struct QueueNode {
    Vehicle          *vehicle;
    QueueNode        *previous;
    QueueNode        *next;
} QueueNode;

typedef struct {
    QueueNode *head;
    QueueNode *tail;
    int        size;
} Queue;