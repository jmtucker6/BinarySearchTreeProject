#include <stdbool.h>

#ifndef BST_H
#define BST_H

typedef struct Node {
    char *key;
    int frequency;
    int level;
    struct Node *parent;
    struct Node *left;
    struct Node *right;

} Node;

typedef struct BST {
    Node *root;
} BST;


extern void insertWord(BST *, Node *,  char *);
extern void deleteWord(BST *, char *);
extern int findKey(BST *, Node *, char *);
extern void increaseNodeFrequency(Node *);
extern void decreaseNodeFrequency(Node *);
extern bool isEmptyTree(BST *);
extern Node *newNode(Node *, char *);

#endif
