/*
 * AVL tree checker, by John C. Lusth
 *
 *    Reads in a specially formatted textual display of a AVL tree
 *    (see http://beastie.cs.ua.edu/cs201/assign2.html)
 *
 *    Performs the following checks on the resulting AVL tree:
 *        Checks that the height of the left child's
 *            subtree does not exceed that of the right's
 *            by more than one (and vice versa)
 *        Checks that BST ordering is maintained
 *            (not implemented, left as an exercise)
 *
 *    WARNING: this code is minimally tested and is not guaranteed to be
 *    correct. In other words, don't come complaining to me if this code
 *    says your AVL tree is correct and it isn't.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "avl.h"

void Fatal(char *,...);

int
main(int argc,char **argv)
    {
    tnode *rbt;
    if (argc != 2)
        Fatal("usage: avlchecker FILENAME\n");

    rbt = readTree(argv[1]);

    printf("Checking for unbalanced nodes...\n");
    (void) checkBalance(rbt);
    printf("Balance check passed.\n");
    printf("Checking for BST ordering...\n");
    checkOrder(rbt);
    printf("BST ordering check passed.\n");
    return 0;
    }

void
Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }

