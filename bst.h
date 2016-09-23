#ifndef BST_H
#define BST_H
#include <stdbool.h>

typedef struct Node {
    char *key;
    int frequency;
    int level;
    struct Node *parent;
    struct Node *left;
    struct Node *right;

} Node;

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
extern Node *newNode(Node *, char *);
extern BST *newBST();
extern void traversal(BST *);

#endif
