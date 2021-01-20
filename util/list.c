#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct lnode *lalloc(void)
{
    return (struct lnode *)malloc(sizeof(struct lnode));
}

struct lnode *appendlist(struct lnode *ptr, int val)
{
    struct lnode *head = ptr;
    struct lnode *prev = NULL;

    if ((ptr = lalloc()) == NULL)
        return NULL;
    ptr->val = val;
    ptr->next = NULL;
    while(ptr)
    {
        prev = ptr; 
        ptr = ptr->next;
    }
    if (prev)
        prev->next = ptr;
    else
        head = ptr;
    return ptr;
}

struct lnode *addflist(struct lnode *ptr, int val)
{
    struct lnode *head;
    
    if ((head = lalloc()) == NULL)
        return ptr;
    head->val = val;
    head->next = ptr;
    return head;
}

void listprint(struct lnode *ptr)
{
    for(; ptr ; ptr = ptr->next)
        printf("%d ", ptr->val);
    printf("\n");
}

void listfree(struct lnode *ptr)
{
    for (struct lnode *p = ptr; p; p = ptr)
    {
        ptr = p->next;
        free(p);
    }
}