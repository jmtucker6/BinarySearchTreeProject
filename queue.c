#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "fatal.h"
#include "node.h"

/*
 * queue.c
 *
 * Implements queue objects
 * Written by Jacob Tucker
 */

/*
 * PUBLIC FUNCTIONS
 */

/*
 * Enqueues onto back (tail) of linked list
 */
void enqueue(Queue *q, Node *node) {
    QueueNode *queueNode = newQueueNode(node);
    if (q -> head == NULL)
        q -> head = queueNode;
    if (q -> tail != NULL)
        q -> tail -> next = queueNode;
    q -> tail = queueNode;    
};

/*
 * Dequeues from front (head) of linked list
 */
Node *dequeue(Queue *q) {
    if (isEmptyQueue(q))
        Fatal("Cannot dequeue from empty queue\n");
    Node *n = q -> head -> data;
    QueueNode *temp = q -> head;
    if (q -> head != q -> tail)
        q -> head = q -> head -> next;
    else {
        q -> head = NULL;
        q -> tail = NULL;
    }
    free(temp);
    return n;
};

/*
 * Duplicates a queue
 */
Queue *duplicateQueue(Queue *q) {
    Queue *newQ = NULL;
    newQ = newQueue();
    QueueNode *node = q -> head;
    while (node != NULL) {
        enqueue(newQ, node -> data);
        node = node -> next;
    }
    return newQ;
};

/*
 * Returns an empty queue
 */
Queue *newQueue(void) {
    Queue *q = malloc(sizeof(Queue));
    if (q == 0)
        Fatal("Insufficient space for new queue\n");
    q -> head = NULL;
    q -> tail = NULL;
    return q;
};

QueueNode *newQueueNode(Node *node) {
    QueueNode *q = malloc(sizeof(QueueNode));
    if (q == NULL)
        Fatal("Out of memory\n");
    q -> data = node;
    q -> next = NULL;
    return q;
};

/*
 * Checks if queue is empty
 */
bool isEmptyQueue(Queue *q) {
    return (q -> head == NULL && q -> tail == NULL) ? true : false;
};

