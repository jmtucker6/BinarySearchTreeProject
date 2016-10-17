#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * avl.c
 *
 * Implementation of an AVL tree
 *
 * Written by Jacob Tucker
 */

static void rotateLeft(BST *tree, Node *node);
static void rotateRight(BST *tree, Node *node);

/**
 * PUBLIC FUNCTIONS
 */

void insertWordAVL(BST *, Node *, char *);
void deleteWordAVL(BST *, char *);
void traversalAVL(BST *);

/**
 * PRIVATE FUNCTIONS
 */

static void rotateLeft(BST *tree, Node *node) {
    Node *newParent = node -> right;
    node -> right = newParent -> left;
    if (newParent -> left != NULL)
        newParent -> left -> parent = node;
    newParent -> parent = node -> parent;
    if (node -> parent == NULL)
        tree -> root = newParent;
    else if (node == node -> parent -> left)
        node -> parent -> left = newParent;
    else
        node -> parent -> right = newParent;
    newParent -> left = node;
    node -> parent = newParent;
};

static void rotateRight(BST *tree, Node *node) {
    Node *newParent = node -> left;
    node -> left = newParent -> right;
    if (newParent -> right != NULL)
        newParent -> right -> parent = node;
    newParent -> parent = node -> parent;
    if (node -> parent == NULL)
        tree -> root = newParent;
    else if (node == node -> parent -> left)
        node -> parent -> left = newParent;
    else
        node -> parent -> right = newParent;
    newParent -> right = node;
    node -> parent = newParent;
};
