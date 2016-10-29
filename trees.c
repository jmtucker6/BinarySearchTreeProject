#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"
#include "avl.h"
#include "fatal.h"
#include "scanner.h"
#include "stats.h"

/**
 * trees.c
 *
 * Main driver for assignment2
 * Converts input into BST instructions
 *
 * Written by Jacob Tucker
 */

typedef enum TreeType {NORMAL, AVL} TreeType;
static char *readNextToken(FILE *);
static char *cleanString(char *);

/**
 * Main function for trees
 * Command Line: ./trees -a/-b [inputFile] [commandFile]
 */
int main(int argc, char **argv)
{
    if (argc < 4)
        Fatal("Too few parameters\n");
    else if (strcmp(argv[1], "-b") != 0 && strcmp(argv[1], "-a") != 0)
        Fatal("Invalid flag\n");
    TreeType treeType = (strcmp(argv[1], "-b") == 0) ? NORMAL : AVL;
    FILE *fp = fopen(argv[2], "r");
    BST *bst = newBST();
    char *temp = readNextToken(fp);
    while(!feof(fp)) {
        temp = cleanString(temp);
        if (temp[0] != '\0') {
            if (treeType == NORMAL) {
                insertWord(bst, bst -> root, temp);
            } else {
                insertWordAVL(bst, bst -> root, temp);
            }
        }
        temp = readNextToken(fp);
    }
    fclose(fp);
    fp = fopen(argv[3], "r");
    temp = readNextToken(fp);
    while(!feof(fp)) {
        temp = cleanString(temp);
        if (temp != '\0') {
            switch(*temp) {
                case 'i':
                    temp = cleanString(readNextToken(fp));
                    if (treeType == NORMAL)
                        insertWord(bst, bst -> root, temp);
                    else
                        insertWordAVL(bst, bst -> root, temp);
                    break;
                case 'd':
                    temp = cleanString(readNextToken(fp));
                    if (treeType == NORMAL)
                        deleteWord(bst, temp);
                    else
                        deleteWordAVL(bst, temp);
                    break;
                case 'f':
                    temp = cleanString(readNextToken(fp));
                    printf("Frequency of \"%s\": %d\n\n", temp, findKey(bst, bst -> root, temp));
                    break;
                case 's':
                    if (treeType == NORMAL)
                        traversal(bst);
                    else
                        traversalAVL(bst);
                    printf("\n");
                    break;
                case 'r':
                    reportStats(bst);
                    printf("\n");
                    break;
            }
        }
        temp = readNextToken(fp);
    }
    return 0;
}

/**
 * Reads next token from a file
 */
static char *readNextToken(FILE *fp) {
    char *s;
    if(stringPending(fp))
        s = readString(fp);
    else
        s = readToken(fp);
    return s;
};

/**
 * Removes non-alpha characters and collapses white space
 */
static char *cleanString(char *s)
{
    char *dest = s, *src = s;
    bool isPrevSpace = false;
    while (*src != '\0') {
        if (isalpha(*src)) {
            *dest = tolower(*src);
            dest++;
            isPrevSpace = false;
        }
        if ((*src == ' ' || *src == '\t') && !isPrevSpace) {
            *dest = ' ';
            dest++;
            isPrevSpace = true;
        }
        src++;
    }
    *dest = '\0';
    return s;

}
