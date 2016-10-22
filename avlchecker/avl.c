/*
 * ALV tree checker, by John C. Lusth
 *
 *    See avlchecker.c for details
 *
 *    This is the implementation for AVL trees
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "avl.h"
#include "queue.h"

extern void Fatal(char *,...);

static tnode *textToNode(char *);
static void setChild(tnode *,tnode *);
static tnode *newTNode(char *,int,char *,tnode *,tnode *,char *,char);

/**************** Public Methods *********************/

/* constructors */

tnode *
readTree(char *filename)
    {
    tnode *root = 0;

    FILE *fp;
    if ((fp = fopen(filename,"r")) == 0)
        Fatal("file %s could not be opened for reading.\n",filename);

    queue *q = newQueue();
    char *t;
    
    t = readToken(fp); //skip the first line number
    t = readToken(fp);
    root = textToNode(t);
    root->parent = root;
    if (root->side != 'X')
        Fatal("root node did not have X designator: %c\n",root->side);
    enqueue(q,root);

    t = readToken(fp);
    while (!feof(fp))
        {
        tnode *tn;
        if (isalpha(*t) || *t == '=')
            {
            tn = textToNode(t);
            enqueue(q,tn);
            //find the parent, it must be on the queue
            while (strcmp(peekQueue(q)->name,tn->parentName) != 0)
                {
                dequeue(q);
                if (isEmptyQueue(q))
                    Fatal("node %s has a misnamed parent: %s\n",
                        tn->name,tn->parentName);
                }
            setChild(peekQueue(q),tn);
            }
        t = readToken(fp);
        }
    return root;
    }

int
checkBalance(tnode *t)
    {
    int LH,RH;

    if (t == 0) return 0;

    LH = checkBalance(t->left);
    RH = checkBalance(t->right);

    if (LH - 1 > RH)
        Fatal("Node %s has a left imbalance\n"
            "that is too large (%d LH vs. %d RH)\n",t->name,LH,RH);

    if (RH - 1 > LH)
        Fatal("Node %s has a right imbalance\n"
            "that is too large (%d LH vs. %d RH)\n",t->name,LH,RH);

    if (*(t->favorite) == '\0' && LH > RH)
        Fatal("Node %s should favor the left,\n"
            "but does not have a favorite (%d LH vs. %d RH)\n",t->name,LH,RH);

    if (*(t->favorite) == '\0' && LH < RH)
        Fatal("Node %s should favor the right,\n"
            "but does not have a favorite (%d LH vs. %d RH)\n",t->name,LH,RH);

    if (*(t->favorite) == '-' && LH == RH)
        Fatal("Node %s favors the left,\n"
            "but should not have a favorite (%d LH vs. %d RH)\n",t->name,LH,RH);

    if (*(t->favorite) == '-' && LH < RH)
        Fatal("Node %s favors the left,\n"
            "but should favor the right (%d LH vs. %d RH)\n",t->name,LH,RH);

    if (*(t->favorite) == '+' && LH == RH)
        Fatal("Node %s favors the right,\n"
            "but should not have a favorite (%d LH vs. %d RH)\n",t->name,LH,RH);

    if (*(t->favorite) == '+' && LH > RH)
        Fatal("Node %s favors the right,\n"
            "but should favor the left (%d LH vs. %d RH)\n",t->name,LH,RH);

    return (LH > RH? LH : RH) + 1;
    }

void
checkOrder(tnode *t)
    {
        if (t -> left == 0 && t -> right == 0)
            return;
        if (t -> left != 0) {
            if (strcmp(t -> left -> name, t -> name) >= 0)
                Fatal("Node %s should be greater than its left child %s\n",
                        t -> name, t -> left -> name);
            checkOrder(t -> left);
        }
        if (t -> right != 0) {
            if (strcmp(t -> right -> name, t -> name) <= 0)
                Fatal("Node %s should be less than its right child %s\n",
                        t -> name, t -> right -> name);
            checkOrder(t -> right);
        }
    }

/**************** Private Methods ********************/

/* constructors */

static tnode *
newTNode(char *n,int count,char *fave,tnode *left,tnode *right,char *pn,char s)
    {
    tnode *tn = malloc(sizeof(tnode));
    if (tn == 0)
        Fatal("out of memory\n");
    if (s != 'X' && s != 'R' && s != 'L')
        Fatal("Node %s has a bad child designator: %c\n",n,s);

    tn->name = n;
    tn->count = count;
    tn->favorite = fave;
    tn->left = left;
    tn->right = right;
    tn->parent = 0;
    tn->parentName = pn;
    tn->side = s;
    return tn;
    }

static tnode *
textToNode(char *t)
    {
    char *word = strtok(t,"()");
    char *parent = strtok(0,"()");
    char *which = strtok(0," \n\t");
    int count = atoi(which);
    char *favorite = "";

    if (word[strlen(word)-1] == '-')
        favorite = "-";
    else if (word[strlen(word)-1] == '+')
        favorite = "+";

    if (*word == '=') ++word;

    while (*which && isdigit(*which)) ++which;

    return newTNode(word,count,favorite,0,0,parent,*which);
    }

/* mutators */

static void 
setChild(tnode *p,tnode *c)
    {
    if (c->side == 'L' && p->left == 0)
        p->left = c;
    else if (c->side == 'L')
        Fatal("Node %s has multiple left children.\n",p->name);
    else if (c->side == 'R' && p->right == 0)
        p->right = c;
    else if (c->side == 'R')
        Fatal("Node %s has multiple right children.\n",p->name);
    c->parent = p;
    }
