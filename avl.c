#include "avl.h"
#include "bst.h"
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

static void insertionFixup(BST *, char *);
static void rotateLeft(BST *, Node *);
static void rotateRight(BST *, Node *);
static void setBalance(Node *);
static bool favorsSibling(Node *);
static Node *favoriteChild(Node *);
static bool isLinear(Node *, Node *, Node *);
static void rotate(BST *, Node *, Node *);

/**
 * PUBLIC FUNCTIONS
 */

void insertWordAVL(BST *tree, Node *parent, char *key) {
    insertWord(tree, parent, key);
    insertionFixup(tree, key);
    tree -> height = tree -> root -> height;
};
void deleteWordAVL(BST *, char *);
void traversalAVL(BST *);

/**
 * PRIVATE FUNCTIONS
 */

static void insertionFixup(BST *tree, char *key) {
    Node *node = findNode(tree, tree->root, key);
    while (node != tree -> root) {
        if (favorsSibling(node)) {
            setBalance(node -> parent);
            return;
        } else if (node -> parent -> balanceFactor == 0) {
            setBalance(node -> parent);
            node = node -> parent;
        } else {
            Node *y = favoriteChild(node);
            Node *p = node -> parent;
            if (y != NULL && !isLinear(y, node, p)) {
                rotate(tree, y, node);
                rotate(tree, y, p);
                setBalance(node);
                setBalance(p);
                setBalance(y);
            } else {
                rotate(tree, node, p);
                setBalance(p);
                setBalance(node);
            }
            return;
        }
    }
}

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

static void setBalance(Node *n) {
    int leftHeight, rightHeight;
    leftHeight = (n -> left == NULL) ? 0 : n -> left -> height;
    rightHeight = (n -> right == NULL) ? 0 : n -> right -> height;
    n -> height = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    n -> balanceFactor = rightHeight - leftHeight;
}

static bool favorsSibling(Node *child) {
    if (child == child -> parent -> left)
        return (child -> parent -> balanceFactor > 0) ? true : false;
    else
        return (child -> parent -> balanceFactor < 0) ? true : false;
}

static Node *favoriteChild(Node *parent) {
    if (parent -> balanceFactor <= 0)           // default return is left
        return parent -> left;
    return parent -> right;
};

static bool isLinear(Node *grandchild, Node *child, Node *parent) {
    if (grandchild == child -> left)
        return (child == parent -> left) ? true : false;
    return (child == parent -> right) ? true : false;
}

static void rotate(BST *tree, Node *src, Node *dest) {
    if (src == dest -> left)
        rotateRight(tree, dest);
    else
        rotateLeft(tree, dest);
}
