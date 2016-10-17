#ifndef NODE_H
#define NODE_H
    
typedef struct Node {
    char *key;
    int frequency;
    int level;
    int height;
    int balanceFactor;
    struct Node *parent;
    struct Node *left;
    struct Node *right;

} Node;

extern Node *newNode (Node *, char *);
#endif
