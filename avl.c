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

static void deleteNodeAVL(BST *, Node *);
static void insertionFixup(BST *, Node *);
static void rotateUpFavoredSubtree(BST *, Node *);
static void deletionFixup(BST *, Node *);
static Node *rotateAfterDelete(BST *, Node *);
static void rotateLeft(BST *, Node *);
static void rotateRight(BST *, Node *);
static void setBalance(Node *);
static bool isParentFavoringSibling(Node *);
static Node *favoriteChild(Node *);
static bool isLinear(Node *, Node *, Node *);
static void rotate(BST *, Node *, Node *);
static int numChildren(Node *);
static void swapNodeKeyFreq(Node *, Node *);
static void deleteLeafNode(Node *);
static char *getFavSymbol(Node *);

/**
 * PUBLIC FUNCTIONS
 */

/**
 * Either increases the frequency of an existing node or inserts a new node
 */
void insertWordAVL(BST *tree, Node *parent, char *key) {
    insertWord(tree, parent, key);
    Node *node = findNode(tree, tree -> root, key);
    if (node -> frequency == 1)
        insertionFixup(tree, findNode(tree, tree -> root, key));
    tree -> height = tree -> root -> height;
};

/**
 * Decreases the frequency of a node and deletes if frequency is 0
 */
void deleteWordAVL(BST *tree, char *key) {
    if(isEmptyTree(tree))
        fprintf(stderr, "Can't Delete from Empty Tree\n");
    Node *node = findNode(tree, tree -> root, key);
    if(node == NULL)
        fprintf(stderr, "Node to Delete Does Not Exist\n");
    decreaseNodeFrequency(node);
    if (node -> frequency == 0)
        deleteNodeAVL(tree, node);
};

/**
 * Prints the AVL tree according to the spec
 */
void traversalAVL(BST *tree) {;
    if (isEmptyTree(tree))
        return;
    setLevels(tree, tree -> root);
    Node *node = tree -> root;
    node -> parent = node;
    enqueue(tree -> q, node);
    for (int i = 0; i < tree -> height; i++) {
        printf("%d:", i);
        while (!isEmptyQueue(tree -> q) && tree -> q -> head -> data -> level == i) {
            node = dequeue(tree -> q);
            printf(" ");
            if (node -> left != NULL)
                enqueue(tree -> q, node -> left);
            if (node -> right != NULL)
                enqueue(tree -> q, node -> right);
            if (node -> right == NULL && node -> left == NULL)
                printf("=");
           printf("%s%s(%s%s)%d", node -> key, getFavSymbol(node),
                    node -> parent -> key, getFavSymbol(node -> parent),
                    node -> frequency);
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

/**
 * PRIVATE FUNCTIONS
 */

/**
 * Removes a node from AVL tree
 */
static void deleteNodeAVL(BST *tree, Node *node) {
    if (numChildren(node) == 0) {
        node -> height = 0;
        deletionFixup(tree, node);
        deleteLeafNode(node);
    } else if (numChildren(node) == 1) {
        if (node -> right != NULL) {
            transplant(tree, node, node -> right);
            deletionFixup(tree, node -> right);
        } else {
            transplant(tree, node, node -> left);
            deletionFixup(tree, node -> left);
        }
    } else {
        Node *succ = treeMinimum(node -> right);
        swapNodeKeyFreq(node, succ);
        deleteNodeAVL(tree, succ);
    }
}

/**
 * Re-establishes AVL balance after an insertion
 */
static void insertionFixup(BST *tree, Node *node) {
    while (node != tree -> root) {
        if (isParentFavoringSibling(node)) {
            setBalance(node -> parent);
            return;
        } else if (node -> parent -> balanceFactor == 0) {
            setBalance(node -> parent);
            node = node -> parent;
        } else {
            rotateUpFavoredSubtree(tree, node);
            return;
        }
    }
}

/*
 * Performs reordering for insertionFixup
 */
static void rotateUpFavoredSubtree(BST *tree, Node *node) {
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
};

/**
 * Re-establishes AVL balance after a deletion
 */
static void deletionFixup(BST *tree, Node *node) {
    while (node != tree -> root) {
        if (node == favoriteChild(node -> parent)) {
            setBalance(node -> parent);
            node = node -> parent;
        } else if (node -> parent -> balanceFactor == 0) {
            setBalance(node -> parent);
            return;
        } else {
            node = rotateAfterDelete(tree, node);
            if (node == NULL)
                return;
        }
    }
};

/**
 * Performs rotation to fix tree imbalance after a deletion
 */
static Node *rotateAfterDelete(BST *tree, Node *node) {
    Node *parent = node -> parent;
    Node *sibling = favoriteChild(parent);      // favorite child is sibling
    Node *y = favoriteChild(sibling);
    if (y != NULL && !isLinear(y, sibling, parent)) {
        rotate(tree, y, sibling);
        rotate(tree, y, parent);
        setBalance(parent);
        setBalance(sibling);
        setBalance(y);
        return y;
    } else {
        rotate(tree, sibling, parent);
        setBalance(parent);
        setBalance(sibling);
        if (y == NULL)
            return NULL;
        return sibling;
    }
}

/**
 * Rotates right child to its parent maintaining BST order
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

/**
 * Rotates left child to its parent maintaining BST order
 */
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

/**
 * Sets height and balance factor for a node
 */
static void setBalance(Node *n) {
    int leftHeight, rightHeight;
    leftHeight = (n -> left == NULL) ? 0 : n -> left -> height;
    rightHeight = (n -> right == NULL) ? 0 : n -> right -> height;
    n -> height = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    n -> balanceFactor = rightHeight - leftHeight;
}

/**
 * Returns true if parent favors the sibling of the parameter node
 */
static bool isParentFavoringSibling(Node *child) {
    if (child == child -> parent -> left)
        return (child -> parent -> balanceFactor > 0) ? true : false;
    else
        return (child -> parent -> balanceFactor < 0) ? true : false;
}

/**
 * Returns the favorite child of the parent
 */
static Node *favoriteChild(Node *parent) {
    if (parent -> balanceFactor < 0)
        return parent -> left;
    else if (parent -> balanceFactor > 0)
        return parent -> right;
    return NULL;
};

/**
 * Returns true if the 3 nodes are linear
 */
static bool isLinear(Node *grandchild, Node *child, Node *parent) {
    if (grandchild == child -> left)
        return (child == parent -> left) ? true : false;
    return (child == parent -> right) ? true : false;
}

/**
 * Rotates src to destination maintaining bst ordering
 */
static void rotate(BST *tree, Node *src, Node *dest) {
    if (src == dest -> left)
        rotateRight(tree, dest);
    else
        rotateLeft(tree, dest);
}

/**
 * Returns the number of children of the node
 */
static int numChildren(Node *node) {
    if (node -> left != NULL)
        return node -> right != NULL ? 2 : 1;
    else if (node -> right != NULL)
        return 1;
    return 0;
}

/**
 * Swaps two nodes keys and frequencies
 */
static void swapNodeKeyFreq(Node *node1, Node *node2) {
    char* tempKey = node1 -> key;
    node1 -> key = node2 -> key;
    node2 -> key = tempKey;

    int tempFreq = node1 -> frequency;
    node1 -> frequency = node2 -> frequency;
    node2 -> frequency = tempFreq;
}

/**
 * Removes a leaf node from the AVL tree
 */
static void deleteLeafNode(Node *node) {
    if (node == node -> parent -> left)
        node -> parent -> left = NULL;
    else
        node -> parent -> right = NULL;
    node -> parent = NULL;
}

/**
 * Returns the character symbol associated with favoritism
 */
static char *getFavSymbol(Node *node) {
    if (node -> balanceFactor < 0)
        return "-";
    else if (node -> balanceFactor > 0)
        return "+";
    return "";
}

