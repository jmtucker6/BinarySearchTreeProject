#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"
#include "fatal.h"
#include "scanner.h"

static char *readNextToken(FILE *);
static char *cleanString(char *);

int main(int argc, char **argv)
{
    if (argc < 4)
        Fatal("Too few parameters\n");
    FILE *fp = fopen(argv[2], "r");
    BST *bst = newBST();
    char *temp = readNextToken(fp);
    while(!feof(fp)) {
        temp = cleanString(temp);
        if (temp[0] != '\0')
            insertWord(bst, bst -> root, temp);
        temp = readNextToken(fp);
    }
    traversal(bst);
    printf("Tree Height: %d\n", bst -> height);
    return 0;
}

static char *readNextToken(FILE *fp) {
    char *s;
    if(stringPending(fp))
        s = readString(fp);
    else
        s = readToken(fp);
    return s;
};

static char *cleanString(char *s)
{
    char *dest = s, *src = s;
    while (*src != '\0') {
        if (isalpha(*src) || *src == ' ') {
            *dest = tolower(*src);
            dest++;
        }
        src++;
    }
    *dest = '\0';
    return s;

}
