#ifndef BST_H
#define BST_H
#include <stdbool.h>
#include "node.h"
#include "queue.h"

typedef struct BST {
    Node *root;
    int height;
    Queue *q;
} BST;


extern void insertWord(BST *, Node *,  char *);
extern void deleteWord(BST *, char *);
extern int findKey(BST *, Node *, char *);
extern void increaseNodeFrequency(Node *);
extern void decreaseNodeFrequency(Node *);
extern bool isEmptyTree(BST *);
extern BST *newBST();
extern void traversal(BST *);
extern Node *findNode(BST *, Node *, char *);
extern void transplant(BST *, Node *, Node *);
extern Node *treeMinimum(Node *);

#endif
