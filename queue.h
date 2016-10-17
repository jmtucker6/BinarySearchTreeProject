#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
typedef struct QueueNode QueueNode;
typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
} Queue;

#include "bst.h"
#include "node.h"
struct QueueNode{
    Node *data;
    struct QueueNode *next;
};


extern void enqueue(Queue *, Node *);
extern Node *dequeue(Queue *);
extern Queue *newQueue(void);
extern QueueNode *newQueueNode(Node *);
extern bool isEmptyQueue(Queue *);
extern Queue *duplicateQueue(Queue *);

#endif
