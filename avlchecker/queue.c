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
        queue *q= malloc(sizeof(queue));
        if (q== 0)
            fprintf(stderr, "Out of Memory\n");
        q-> head = 0;
        q-> tail = 0;
        return q;
    }


/* standard queue methods */

tnode *
peekQueue(queue *q)
    {
    return q -> head -> value;
    }

void
enqueue(queue *q,tnode *value)
    {
        if (isEmptyQueue(q)) {
            q -> head = newQNode(value, 0);
            q -> tail = q-> head;
        } else {
            q -> tail -> next = newQNode(value, 0);
            q -> tail = q -> tail -> next;
        }
    }

tnode *
dequeue(queue *q)
    {
        qnode *node = q -> head;
        q -> head = q -> head -> next;
        return node -> value;
    }

int
isEmptyQueue(queue *q)
    {
        return (q -> head == NULL) ? 1 : 0;
    }

/**************** Private Methods ********************/

/*
 * constructor for a node in a linked-list based queue 
 * this constructor will be used by enqueue - right now
 * it generates a compiler warning (which will go away
 * once enqueue is implemented.
 *
 */

static qnode *
newQNode(tnode *value,qnode *next)
    {
    qnode *qn = malloc(sizeof(qnode));
    if (qn == 0) Fatal("out of memory\n");
    qn->value = value;
    qn->next = next;
    return qn;
    }
