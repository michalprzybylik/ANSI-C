#include <stdlib.h>
#include <stdio.h>
#include "list.h"

Nodeptr nodealloc(void)
{
    return (Nodeptr)malloc(sizeof(Listnode));
}

Nodeptr appendlist(Nodeptr *ptr, int val)
{
    while(*ptr)
        ptr = &(*ptr)->next;

    if ((*ptr = nodealloc()) == NULL)
        return NULL;
    (*ptr)->val = val;
    (*ptr)->next = NULL;
    return *ptr;
}

Nodeptr addlist(Nodeptr *ptr, int val)
{
    Nodeptr head;

    if ((head = nodealloc()) == NULL)
        return NULL;
    head->val = val;
    head->next = *ptr;
    *ptr = head;
    return *ptr;
}

Nodeptr findlist(Nodeptr ptr, int val)
{
    for(; ptr; ptr = ptr->next)
        if (ptr->val == val)
            return ptr;
    return NULL;
}

void printlist(Nodeptr ptr)
{
    for (; ptr; ptr = ptr->next)
        printf("%d ", ptr->val);
    printf("\n");
}

void removenode(Nodeptr *ptr, int val)
{
    Nodeptr tmp = NULL;

    while ((*ptr) && (*ptr)->val != val)
        ptr = &(*ptr)->next;

    if (*ptr)
    {
        tmp = *ptr;
        *ptr = (*ptr)->next;
        free(tmp);
    }
}

void freelist(Nodeptr ptr)
{
    for (Nodeptr p = ptr; p; p = ptr)
    {
        ptr = p->next;
        free(p);
    }
}