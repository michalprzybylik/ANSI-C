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

    ptr = lalloc();
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
    return head;
}

struct lnode *addflist(struct lnode *ptr, int val)
{
    struct lnode *head;
    head = lalloc();
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
    struct lnode *tmp = NULL;
    while(ptr)
    {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}