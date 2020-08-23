#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum tokentypes
{
    WORD,
    COMMENT,
    STRING
};

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 128
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char*, int);
void treefree(struct tnode *);

int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD] = "";
    char type = '\0';

    while((type = getword(word, MAXWORD)) != EOF)
        if(type == WORD)
            root = addtree(root, word);
    treeprint(root);
    treefree(root);
    return 0;
}

int getword(char *word, int lim)
{
    int c = 0, d = 0;
    char *w = word;

    while(isspace(c = getchar()))
        ;
    if(c != EOF)
        *w++ = c;
    if(isalpha(c) || c == '_' || c == '#')
    {
        for(; --lim > 0; w++)
            if(!isalnum(*w = getchar()) && *w != '_')
            {
                ungetc(*w, stdin);
                break;
            }
        *w = '\0';
        return WORD;
    }
    if( c == '\'' || c == '"')
    {
        for(; --lim > 0; w++)
            if((*w = getchar()) == '\\')
                *++w = getchar();
            else if (*w == c)
            {
                ++w;
                break;
            }
            else if (*w == EOF)
                break;
        return STRING;
    }
    if (c == '/')
    {
        if ((d = getchar()) == '/')
        {
            while(getchar() != '\n')
                ;
        }
        if (d == '*')
        {
            while((c = getchar()) != EOF)
                if(c == '*')
                {
                    if((c = getchar()) == '/')
                        break;
                    else
                        ungetc(c, stdin);
                }
        }
        else
            ungetc(d, stdin);
        return COMMENT;
    }
    *w = '\0';
    return c;
}

struct tnode *addtree(struct tnode *ptr, char *str)
{
    int comp = 0;

    if (ptr == NULL)
    {
        ptr = (struct tnode *)malloc(sizeof(struct tnode));
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

void treeprint(struct tnode *ptr)
{
    if (ptr != NULL)
    {
        treeprint(ptr->left);
        printf("%5d %s\n", ptr->count, ptr->word);
        treeprint(ptr->right);
    }
}

void treefree(struct tnode *ptr)
{
    if (ptr != NULL)
    {
        treefree(ptr->left);
        free(ptr->word);
        treefree(ptr->right);
    }
    free(ptr);
}