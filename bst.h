#include <stdbool.h>

#ifndef BST_H
#define BST_H

typedef struct Node {
    char *key;
    int frequency;
    struct Node *parent;
    struct Node *left;
    struct Node *right;

} Node;


extern Node *insertWord(Node *, Node *,  char *);
extern Node *deleteWord(Node *, char *);
extern int findKey(Node *, char *);
extern Node *increaseNodeFrequency(Node *);
extern Node *decreaseNodeFrequency(Node *);
extern bool isEmptyTree(Node *);
extern Node *newNode(Node *, char *);

#endif
