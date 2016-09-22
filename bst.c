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

static Node *findNode(BST *, Node *, char *);
static void deleteNode(BST *, char *);
/*
 * PUBLIC FUNCTIONS
 */

/*
 * Inserts a key-data pair into the binary search tree
 */

void insertWord(BST *tree, Node *parent, char *key) {
    if (isEmptyTree(tree)) {
        tree -> root = newNode(NULL, key);
        tree -> root -> parent = tree -> root;
        return;
    }
    if (strcmp(key, parent -> key) == 0) {
        increaseNodeFrequency(parent);
    } else if (strcmp(key, parent -> key) < 0) {
        if (parent -> left == NULL) {
            parent -> left = newNode(parent, key);
        } else {
            insertWord(tree, parent -> left, key);
        }
    } else {
        if (parent -> right == NULL) {
            parent -> right = newNode(parent, key);
        } else {
            insertWord(tree, parent -> left, key);
        }
    }
};

/*
 * Deletes a word from the tree (decreases frequency)
 */
void deleteWord(BST *tree, char *key) {
    Node *node = findNode(tree, tree -> root, key);
    if (node == NULL)
        fprintf(stderr, "Can't delete a word that is not in the tree\n");
    decreaseNodeFrequency(node);
    if (node -> frequency <= 0)
        deleteNode(tree, key);
};

/*
 * Returns the frequency paired with the given key
 */
int findKey(BST *tree, Node *node, char *key) {
    Node *temp = findNode(tree, node, key);
    return (temp == NULL) ? -1 : temp -> frequency;
};

/*
 * Increases frequency of a node
 */
void increaseNodeFrequency(Node *root) {
    root -> frequency++;
};

/*
 * Decreases frequency of a node
 */
void decreaseNodeFrequency(Node *node) {
    node -> frequency--;
};

/*
 * Returns if the tree is empty
 */
bool isEmptyTree(BST *tree) {
    if (tree -> root == NULL)
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
    node -> level = (parent == NULL) ? 0 : parent -> level;
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
static Node *findNode(BST *tree, Node *node, char *key) {
    if (isEmptyTree(tree))
        return NULL;
    int comp = strcmp(key, node -> key);
    if (comp > 0) {
        return findNode(tree, node -> right, key);
    } else if (comp < 0) {
        return findNode(tree, node -> left, key);
    } else {
        return node;
    }
    return NULL;
};

/*
 * Removes a node from the tree, and then fixes the tree
 */
static void deleteNode(BST *tree, char *key)
{
    if (isEmptyTree(tree))
        fprintf(stderr, "Cannot delete from empty tree\n");
    fprintf(stderr, "Delete Node on %s  not implemented\n", key);
};
