/*
 * Queue for an AVL tree checker, by John C. Lusth
 *
 *    See avlchecker.c for details
 *
 *    This is the implementation for the queue that is used to
 *    rebuild an AVL tree.
 *
 *    tnodes are AVL tree nodes; the queue holds these
 */

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "queue.h"

extern void Fatal(char *,...);

static qnode *newQNode(tnode *,qnode *);

/**************** Public Methods *********************/

/* constructors */

queue *
newQueue(void)
    {
    queue *q = malloc(sizeof(queue));
    if (q == 0) Fatal("out of memory\n");
    q->head = 0;
    q->tail = 0;
    return q;
    }


/* standard queue methods */

tnode *
peek(queue *q)
    {
    return q->head->value;
    }

void
enqueue(queue *q,tnode *value)
    {
    if (q->head == 0)
        {
        q->head = newQNode(value,0);
        q->tail = q->head;
        }
    else
        {
        q->tail->next = newQNode(value,0);
        q->tail = q->tail->next;
        }
    }

tnode *
dequeue(queue *q)
    {
    tnode *temp = q->head->value;
    q->head = q->head->next;
    if (q->head == 0) q->tail = 0;
    return temp;
    }

int
isEmpty(queue *q)
    {
    return q->head == 0;
    }

/**************** Private Methods ********************/

/* constructor for a node in a linked-list based queue */

static qnode *
newQNode(tnode *value,qnode *next)
    {
    qnode *qn = malloc(sizeof(qnode));
    if (qn == 0) Fatal("out of memory\n");
    qn->value = value;
    qn->next = next;
    return qn;
    }
