/*
 * AVL tree checker, by John C. Lusth
 *
 *    See avlchecker.c for details
 *
 *    This is the public interface for AVL trees
 *
 */

typedef struct tnode        /* this is a AVL tree node */
    {
    char *name;
    struct tnode *parent;
    struct tnode *left;
    struct tnode *right;
    char *favorite;
    int count;
    char side;
    char *parentName;
    } tnode;

/************ Public Interface **************/

/* constructors */

extern tnode *readTree(char *);

/* integrity checkers */

extern int checkBalance(tnode *);
extern void checkOrder(tnode *);
