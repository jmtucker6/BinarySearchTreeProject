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

static tnode *readNode(FILE *);
static char *readUntil(FILE *,char *);
static void setChild(tnode *,tnode *);
static tnode *newTNode(char *,int,char *,tnode *,tnode *,char *,char);
static void skipLineNumber(FILE *);

/**************** Public Methods *********************/

/* constructors */

tnode *
readTree(char *filename)
    {
    int ch;
    tnode *root = 0;

    FILE *fp;
    if ((fp = fopen(filename,"r")) == 0)
        Fatal("file %s could not be opened for reading.\n",filename);

    queue *q = newQueue();
    
    skipLineNumber(fp);
    root = readNode(fp);
    root->parent = root;
    if (strcmp(root->name,root->parentName) != 0)
        Fatal("root node does not have itself as its parent\n");
    if (root->side != 'X')
        Fatal("root node did not have X designator: %c\n",root->side);
    enqueue(q,root);

    skipLineNumber(fp);
    while (!feof(fp))
        {
        tnode *tn = readNode(fp);
        if (tn == 0)
            Fatal("premature end of file\n");
        enqueue(q,tn);
        //find the parent, it must be on the queue
        while (strcmp(peek(q)->name,tn->parentName) != 0)
            {
            dequeue(q);
            if (isEmpty(q))
                Fatal("node %s has a misnamed parent: %s\n",
                    tn->name,tn->parentName);
            }
        setChild(peek(q),tn);
        ch = fgetc(fp);
        if (ch == '\n')
            skipLineNumber(fp);
        }
    return root;
    }

static void
skipLineNumber(FILE *fp)
    {
    int ch;
    (void) readToken(fp); //skip over the line number
    if (feof(fp)) return;
    ch = fgetc(fp);
    if (ch != ' ')
        Fatal("expected space after line number:\n");
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
    //Fatal("checkOrder has not been implemented.\n");
    if (t == 0) return;
    if (t->left != 0)
        {
        if (strcmp(t->left->name,t->name) >= 0)
            Fatal("Node %s is out of order; left value is %s.\n",
                t->name,t->left->name);
        checkOrder(t->left);
        }
    if (t->right != 0)
        {
        if (strcmp(t->right->name,t->name) <= 0)
            Fatal("Node %s is out of order; right value is %s.\n",
                t->name,t->right->name);
        checkOrder(t->right);
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
readNode(FILE *fp)
    {
    int ch;
    char *word;
    char *parent;
    int count;
    char *favorite = "";
    char which;

    word = readUntil(fp,"(");

    if (feof(fp)) return 0;

    if (word[strlen(word)-1] == '+')
        favorite = "+";
    else if (word[strlen(word)-1] == '-')
        favorite = "-";

    //printf("word is %s\n",word);
    //printf("favorite is \"%s\"\n",favorite);

    ch = fgetc(fp);

    if (feof(fp)) return 0;

    if (ch != '(')
        Fatal("bad character follows %s: '%c'\n",word,ch);

    parent = readUntil(fp,")");
    //printf("parent is %s\n",parent);

    if (feof(fp)) return 0;

    ch = fgetc(fp);
       
    if (feof(fp)) return 0;

    if (ch != ')')
        Fatal("bad character follows %s,%s: '%c'\n",word,parent,ch);

    fscanf(fp,"%d",&count);
    //printf("count is %d\n",count);

    if (feof(fp)) return 0;

    if (count == 0)
        Fatal("bad frequency\n");

    which = fgetc(fp);

    if (feof(fp)) return 0;

    if (strchr("XLR",which) == 0)
        Fatal("Bad side designator for %s: %c\n",word,ch);

    //printf("side is %c\n",which);
    return newTNode(word,count,favorite,0,0,parent,which);
    }


static char *
readUntil(FILE *fp,char *stop)
    {
    int i;
    int ch;
    int space = 0;
    int buffersize = 512;
    char *buffer,*result;

    if ((buffer = malloc(buffersize)) == 0)
        Fatal("out of memory\n");

    ch = fgetc(fp);
    /* skip over leaf designator */
    if (ch == '=')
        ch = fgetc(fp);
      
    i = 0;
    while (ch != EOF && strchr(stop,ch) == 0)
        {
        // printf("ch is %c\n",ch);
        if (!isalpha(ch) && strchr(" +-",ch) == 0)
            Fatal("bad character: '%c'\n",ch);

        if (ch == ' ' && space)
            Fatal("multiple consecutive spaces\n");
        else if (ch == ' ')
            space = 1;
        else
            space = 0;

        /* grow the array if necessary */
        if (i == buffersize)
            {
            if ((buffer = realloc(buffer,buffersize * 2)) == 0)
                Fatal("out of memory\n");
            buffersize *= 2;
            }

        buffer[i++] = ch;
        ch = fgetc(fp);
        }

    buffer[i] = '\0';

    ungetc(ch,fp);

    if ((result = strdup(buffer)) == 0)
        Fatal("out of memory\n");

    free(buffer);

    return result;
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
