/*
Zadanie 6.04. Napisz program, który zlicza różne słowa podane na wejściu i wypisuje 
je uporządkowane według malejącej krotności ich wystąpień. Każde słowo 
poprzedź jego krotnością. 
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 128

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *);
void treefree(struct tnode *);
int countnodes(struct tnode *);
void storeptrs(struct tnode *, struct tnode **, int);
int getword(char *, int);
int tncmp(const void *, const void *);

int main(int argc, char *argv[])
{
    int nodes = 0;
    struct tnode *root = NULL;
    struct tnode **ptrtable = NULL;
    char word[MAXWORD] = "";
    
    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
            root = addtree(root, word);
    }
    nodes = countnodes(root);
    ptrtable = (struct tnode **)malloc(nodes * sizeof(struct tnode **));
    storeptrs(root, ptrtable, nodes);
    qsort(ptrtable, nodes, sizeof(struct tnode *), tncmp);
    for (int i = 0; i < nodes; ++i)
        printf("%4d %s\n", ptrtable[i]->count, ptrtable[i]->word);
    treefree(root);
    free(ptrtable);
    return 0;
}

int getword(char *word, int lim)
{
    int c = 0, d = 0;
    char *w = word;

    while (isspace(c = getchar()) && c != '\n')
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
    {
        if (!isalnum(*w = getchar()))
        {
            ungetc(*w, stdin);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *ptr, char *str)
{
    int comp = 0;
    if (ptr == NULL)
    {
        ptr = talloc();
        ptr->word = strdup(str);
        ptr->count = 1;
        ptr->left = ptr->right = NULL;
    }
    else if ((comp = strcmp(str, ptr->word)) == 0)
        ++ptr->count;
    else if (comp < 0)
        ptr->left = addtree(ptr->left, str);
    else
        ptr->right = addtree(ptr->right, str);
    return ptr;
}

int countnodes(struct tnode *ptr)
{
    if (ptr->left == NULL && ptr->right == NULL)
        return 1;
    else if (ptr->left == NULL)
        return 1 + countnodes(ptr->right);
    else if (ptr->right == NULL)
        return 1 + countnodes(ptr->left);
    else
        return 1 + countnodes(ptr->left) + countnodes(ptr->right);
}

void storeptrs(struct tnode *ptr, struct tnode **ptrtable, int lim)
{
    static int i = 0;
    if (ptr != NULL)
    {
        storeptrs(ptr->left, ptrtable, lim);
        if (i < lim)
            ptrtable[i++] = ptr;
        storeptrs(ptr->right, ptrtable, lim);
    }
}

void treefree(struct tnode *ptr)
{
    if (ptr != NULL)
    {
        treefree(ptr->left);
        treefree(ptr->right);
    }
    free(ptr);
}

int tncmp(const void *p1, const void *p2)
{
    struct tnode *ptn1 = *(struct tnode **)p1;
    struct tnode *ptn2 = *(struct tnode **)p2;
    return ptn2->count - ptn1->count;
}