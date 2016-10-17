#include "node.h"
#include "fatal.h"
#include <stdbool.h>
#include <stdlib.h>

/*
 * Creates a new node
 */
Node *newNode(Node *parent, char *key) {
    Node *node = NULL;
    node = malloc(sizeof(Node));
    if (node == NULL)
        Fatal("Out of Mememory\n");
    node -> key = key;
    node -> frequency = 1;
    node -> level = (parent == NULL) ? 1 : parent -> level + 1;
    node -> parent = parent;
    node -> balanceFactor = 0;
    node -> left = NULL;
    node -> right = NULL;
    return node;
};
