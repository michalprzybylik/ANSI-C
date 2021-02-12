#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *ptr, int val)
{
    if (ptr == NULL)
    {
        ptr = talloc();
        ptr->val = val;
        ptr->left = ptr->right = NULL;
    }
    else if (val < ptr->val)
        ptr->left = addtree(ptr->left, val);
    else
        ptr->right = addtree(ptr->right, val);
    return ptr;
}

void printtree(struct tnode *ptr)
{
    if (ptr != NULL)
    {
        treeprint(ptr->left);
        printf("%d\n", ptr->val);
        treeprint(ptr->right);
    }
}

void freetree(struct tnode *ptr)
{
    if (ptr != NULL)
    {
        treefree(ptr->left);
        treefree(ptr->right);
    }
    free(ptr);
}

struct tnode *searchtree(struct tnode *ptr, int val)
{
    if (ptr == NULL || val == ptr->val)
        return ptr;
    else if (val < ptr->val)
        return searchtree(ptr->left, val);
    else
        return searchtree(ptr->right, val);
}

struct tnode *mintnode(struct tnode *ptr)
{
    return (ptr->left) ? mintnode(ptr->left) : ptr;
}

struct tnode *maxtnode(struct tnode *ptr)
{
    return (ptr->right) ? mintnode(ptr->right) : ptr;
}