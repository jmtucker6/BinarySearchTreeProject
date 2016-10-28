#include "fatal.h"
#include "node.h"
#include "bst.h"
#include "queue.h"
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

static void deleteNode(BST *, Node *);
/*
 * PUBLIC FUNCTIONS
 */

/*
 * Inserts a key-data pair into the binary search tree
 */

void insertWord(BST *tree, Node *parent, char *key) {
    if (isEmptyTree(tree)) {
        tree -> root = newNode(NULL, key);
        tree -> height = 1;
        return;
    }
    if (strcmp(key, parent -> key) == 0) {
        increaseNodeFrequency(parent);
    } else if (strcmp(key, parent -> key) < 0) {
        if (parent -> left == NULL) {
            parent -> left = newNode(parent, key);
            tree -> height = (parent -> left -> level > tree -> height) 
                ? parent -> left -> level : tree -> height;
        } else {
            insertWord(tree, parent -> left, key);
        }
    } else {
        if (parent -> right == NULL) {
            parent -> right = newNode(parent, key);
            tree -> height = (parent -> right -> level > tree -> height) 
                ? parent -> right -> level : tree -> height;
        } else {
            insertWord(tree, parent -> right, key);
        }
    }
};

/*
 * Deletes a word from the tree (decreases frequency)
 */
void deleteWord(BST *tree, char *key) {
    Node *node = findNode(tree, tree -> root, key);
    if (node == NULL) {
        fprintf(stderr, "Can't delete a word that is not in the tree\n");
        return;
    }
    decreaseNodeFrequency(node);
    if (node -> frequency <= 0)
        deleteNode(tree, node);
};

/*
 * Returns the frequency paired with the given key
 */
int findKey(BST *tree, Node *node, char *key) {
    Node *temp = findNode(tree, node, key);
    return (temp == NULL) ? 0 : temp -> frequency;
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
 * Creates a new BST
 */
BST *newBST(void)
{
    BST *bst = NULL;
    bst = malloc(sizeof(BST));
    if (bst == NULL)
        Fatal("Out of Memory\n");
    bst -> root = NULL;
    bst -> height = 0;
    bst -> q = newQueue();
    return bst;
};

void traversal(BST *tree)
{
    if (isEmptyTree(tree))
        return;
    tree -> height = 0;
    setLevels(tree, tree -> root);
    Node *node = tree -> root;
    node -> parent = node;
    enqueue(tree -> q, node);
    for (int i = 0; i < tree -> height; i++) {
        printf("%d:", i);
        while (!isEmptyQueue(tree -> q) && tree -> q -> head -> data -> level == i) {
            printf(" ");
            node = dequeue(tree -> q);
            if (node -> left != NULL)
                enqueue(tree -> q, node -> left);
            if (node -> right != NULL)
                enqueue(tree -> q, node -> right);
            if (node -> right == NULL && node -> left == NULL)
                printf("=");
            printf("%s(%s)%d", node -> key, node -> parent -> key, node -> frequency);
            if (node == node -> parent -> left)
                printf("L");
            else if (node == node -> parent -> right) {
                printf("R");
            } else {
                printf("X");
            }
        }
        printf("\n");
    };
}

void setLevels(BST *tree, Node *node) {
    node -> level = (node == tree -> root) ? 0 : node -> parent -> level + 1;
    tree -> height = (tree -> height < node -> level + 1) ? node -> level + 1
        : tree -> height;
    if (node -> left != NULL)
        setLevels(tree, node -> left);
    if (node -> right != NULL)
        setLevels(tree , node -> right);
}

/*
 * PRIVATE FUNCTIONS
 */

/*
 * Returns the node assosciated with its key
 */
Node *findNode(BST *tree, Node *node, char *key) {
    if (isEmptyTree(tree))
        return NULL;
    if (node == NULL)
        return NULL;
    int comp = strcmp(key, node -> key);
    if (comp > 0) {
        return findNode(tree, node -> right, key);
    } else if (comp < 0) {
        return findNode(tree, node -> left, key);
    } else {
        return node;
    }
};

/*
 * Removes a node from the tree, and then fixes the tree
 */
static void deleteNode(BST *tree, Node *node)
{
    Node *y;
    if (node -> left == NULL) {
        transplant(tree, node, node -> right);
        node -> parent = NULL;
    } else if (node -> right == NULL) {
        transplant(tree, node, node -> left);
        node -> parent = NULL;
    } else {
        y = treeMinimum(node -> right);             // y = successor of x
        if (y -> parent != node) {
            transplant(tree, y, y -> right);
            y -> right = node -> right;
            y -> right -> parent = y;
        }
        transplant(tree, node, y);
        y -> left = node -> left;
        y -> left -> parent = y;
    }
    // if (isEmptyTree(tree))
    //     fprintf(stderr, "Cannot delete from empty tree\n");
    // fprintf(stderr, "Delete Node on %s  not implemented\n", key);
};

Node *treeMinimum(Node *root) {
    while (root -> left != NULL)
        root = root -> left;
    return root;
};


void transplant(BST *tree, Node *currNode, Node *replacement) {

    if (currNode == tree -> root)
        tree -> root = replacement;
    else if (currNode == currNode -> parent -> left)
        currNode -> parent -> left = replacement;
    else 
        currNode -> parent -> right = replacement;
    if (replacement != NULL)
        replacement -> parent = currNode -> parent;
};

