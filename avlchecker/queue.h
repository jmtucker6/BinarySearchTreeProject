/*
 * Queue for an AVL tree checker, by John C. Lusth
 *
 *    See avlchecker.c for details
 *
 *    This is the public interface for the queue that is used to
 *    rebuild a AVL tree.
 */

typedef struct qnode
    {
    struct qnode *next;
    struct tnode *value;           /* tnode is an AVL tree node */
    } qnode;

typedef struct queue
    {
    qnode *head;
    qnode *tail;
    } queue;

/************ Public Interface **************/

/* constructors */

queue *newQueue(void);

/* standard queue methods */

tnode *peekQueue(queue *q);
void enqueue(queue *q,tnode *value);
tnode *dequeue(queue *q);
int isEmptyQueue(queue *q);
