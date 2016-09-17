#include "fatal.h"
#include "bst.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * bst.c
 *
 * Implementation of a standard binary search tree
 *
 * Written by Jacob Tucker
 */

static Node *findNode(Node *, char *);
static Node *deleteNode(Node *, char *);
/*
 * PUBLIC FUNCTIONS
 */

/*
 * Inserts a key-data pair into the binary search tree
 */
Node *insertWord(Node *root, Node *parent,  char *key) {
    if (root == NULL) {
        root = newNode(parent, key);
    } else if (strcmp(root -> key, key) == 0) {
        root = increaseNodeFrequency(root);
    } else if (strcmp(key, root -> key) <= 0) {
        root -> left = insertWord(root -> left, root,  key);
    } else {
        root -> right = insertWord(root -> right, root,  key);
    }
        return root;
};

/*
 * Deletes a word from the tree (decreases frequency)
 */
Node *deleteWord(Node *root, char *key) {
    Node *node = findNode(root, key);
    if (node == NULL)
        fprintf(stderr, "Can't delete a word that is not in the tree\n");
    node = decreaseNodeFrequency(node);
    if (node -> frequency <= 0)
        root = deleteNode(root, key);
    return root;
}

/*
 * Returns the frequency paired with the given key
 */
int findKey(Node *root, char *key) {
    if (isEmptyTree(root))
        return -1;
    int comp = strcmp(key, root -> key);
    if (comp > 0) {
        return findKey(root -> right, key);
    } else if (comp < 0) {
        return findKey(root -> left, key);
    } else {
        return root -> frequency;
    }
    return -1;
};

/*
 * Increases frequency of a node
 */
Node *increaseNodeFrequency(Node *root) {
    root -> frequency++;
    return root;
};

/*
 * Decreases frequency of a node
 */
Node *decreaseNodeFrequency(Node *node) {
    node -> frequency--;
    return node;
};

/*
 * Returns if the tree is empty
 */
bool isEmptyTree(Node *root) {
    if (root == NULL)
        return true;
    return false;
};

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
    node -> parent = parent;
    node -> left = NULL;
    node -> right = NULL;
    return node;
};

/*
 * PRIVATE FUNCTIONS
 */

/*
 * Returns the node assosciated with its key
 */
static Node *findNode(Node *root, char *key) {
    if (isEmptyTree(root))
        return NULL;
    int comp = strcmp(key, root -> key);
    if (comp > 0) {
        return findNode(root -> right, key);
    } else if (comp < 0) {
        return findNode(root -> left, key);
    } else {
        return root;
    }
    return NULL;
};

/*
 * Removes a node from the tree, and then fixes the tree
 */
static Node * deleteNode(Node *root, char *key)
{
    fprintf(stderr, "Delete Node on %s  not implemented\n", key);
    return root;
};
