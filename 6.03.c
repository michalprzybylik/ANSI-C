/*
Zadanie 6.03. Napisz program tworzący skorowidz, tj. wypisujący listę wszystkich 
słów dokumentu i dla każdego słowa listę numerów wierszy, w których 
to słowo wystąpiło. Ze skorowidza usuń słowa-ozdobniki w rodzaju "ten", 
"lub" itp.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXWORD 128
#define IGNSIZE (sizeof ignwords / sizeof ignwords[0])

struct lnode
{
    int val;
    struct lnode *next;
};

struct tnode
{
    char *word;
    struct lnode *list;
    struct tnode *left;
    struct tnode *right;
};

char *ignwords[] =
{
    "i",
    "lub",
    "ta",
    "ten",
    "to"
};

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
void treefree(struct tnode *);
struct lnode *lalloc(void);
struct lnode *addlist(struct lnode *, int);
void listprint(struct lnode *);
void listfree(struct lnode *);
int getword(char *, int);
bool isignword(char *);
int binsearch(char *, char *[], int);


int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD] = "";
    int nline = 1;
    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0]) && !isignword(word))
            root = addtree(root, word, nline);
        else if(word[0] == '\n')
            ++nline;
    }
    treeprint(root);
    treefree(root);
    return 0;
}

int getword(char *word, int lim)
{
    int c = 0, d = 0;
    char *w = word;

    while(isspace(c = getchar()) && c != '\n')
        ;
    if(c != EOF)
        *w++ = c;
    if(!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for(; --lim > 0; w++)
    {
        if(!isalnum(*w = getchar()))
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

struct tnode *addtree(struct tnode *ptr, char *str, int nline)
{
    int comp = 0;
    if (ptr == NULL)
    {
        ptr = talloc();
        ptr->word = strdup(str);
        ptr->list = addlist(NULL, nline);
        ptr->left = ptr->right = NULL;
    }
    else if ((comp = strcmp(str, ptr->word)) == 0)
        ptr->list = addlist(ptr->list, nline);
    else if (comp < 0)
        ptr->left = addtree(ptr->left, str, nline);
    else
        ptr->right = addtree(ptr->right, str, nline);
    return ptr;
}

void treeprint(struct tnode *ptr)
{
    if (ptr != NULL)
    {
        treeprint(ptr->left);
        printf("%s: ", ptr->word);
        listprint(ptr->list);
        treeprint(ptr->right);
    }
}

void treefree(struct tnode *ptr)
{
    if (ptr != NULL)
    {
        treefree(ptr->left);
        listfree(ptr->list);
        treefree(ptr->right);
    }
    free(ptr);
}

struct lnode *lalloc(void)
{
    return (struct lnode *)malloc(sizeof(struct lnode));
}

struct lnode *addlist(struct lnode *ptr, int val)
{
    struct lnode *head = ptr;
    struct lnode *prev = NULL;
    for(;ptr != NULL; prev = ptr, ptr = ptr->next)
        if (ptr->val == val)
            return head;
    ptr = lalloc();
    ptr->val = val;
    ptr->next = NULL;
    if (prev)
        prev->next = ptr;
    else
        head = ptr;
    return head;
}

void listprint(struct lnode *ptr)
{
    for(;ptr != NULL; ptr = ptr->next)
        printf("%d ", ptr->val);
    printf("\n");
}


void listfree(struct lnode *ptr)
{
    struct lnode *tmp = NULL;
    while(ptr)
    {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

int binsearch(char *s, char *tab[], int n)
{
    int low = 0, high = n - 1, mid;
    int cmp = 0;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if((cmp = strcmp(s, tab[mid])) < 0)
            high = mid - 1;
        else if (cmp > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

bool isignword(char *s)
{
    if (binsearch(s, ignwords, IGNSIZE) != -1)
        return true;
    else
        return false;
}