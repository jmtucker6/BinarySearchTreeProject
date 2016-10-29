#include "stats.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * stats.c
 *
 * Adds functionality for reporting statistics of a BST
 *
 * Written by Jacob Tucker
 */

static int countNodes(Node *);
static int closestNull(BST *, Queue *, Node *);

/**
 * PUBLIC FUNCTIONS
 */

/*
 * Calls functions to print number of nodes, closest null and farthest null
 */
void reportStats(BST *tree) {
    printf("Number of Nodes: %d\n",countNodes(tree -> root));
    if (isEmptyTree(tree))
        return;
    Queue *queue = newQueue();
    setLevels(tree, tree -> root);
    printf("Closest Node w/ Null child: %d\n", closestNull(tree, queue, tree -> root));
    printf("Farthest Node w/ Null child: %d\n", tree -> height - 1);
}

/*
 * PRIVATE FUNCTIONS
 */

/*
 * Returns number of nodes in BST
 */
static int countNodes(Node *node) {
    if (node == NULL)
        return 0;
    return countNodes(node -> left) + 
        countNodes(node -> right) + 1;
}

/*
 * Returns level of node with closest null child
 */
static int closestNull(BST *tree, Queue *queue, Node *node) {
    if (node -> right == NULL || node -> left == NULL)
        return node -> level;
    else {
        enqueue(queue, node -> left);
        enqueue(queue, node -> right);
        return closestNull(tree, queue, dequeue(queue));
    }
}
