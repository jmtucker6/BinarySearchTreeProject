#include "stats.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

static int countNodes(Node *);
static int closestNull(BST *, Queue *, Node *);

/**
 * PUBLIC FUNCTIONS
 */
void reportStats(BST *tree) {
    if (isEmptyTree(tree))
        return;
    Queue *queue = newQueue();
    printf("Number of Nodes: %d\n",countNodes(tree -> root));
    printf("Closest Node w/ Null child: %d\n", closestNull(tree, queue, tree -> root));
    printf("Farthest Node w/ Null child: %d\n", tree -> height - 1);
}

/*
 * PRIVATE FUNCTIONS
 */
static int countNodes(Node *node) {
    if (node == NULL)
        return 0;
    return countNodes(node -> left) + 
        countNodes(node -> right) + 1;
}

static int closestNull(BST *tree, Queue *queue, Node *node) {
    if (node == tree -> root)
        node -> level = 1;
    else
        node -> level = node -> parent -> level + 1;
    if (node -> right == NULL || node -> left == NULL)
        return node -> level - 1;
    else {
        enqueue(queue, node -> left);
        enqueue(queue, node -> right);
        return closestNull(tree, queue, dequeue(queue));
    }
}
