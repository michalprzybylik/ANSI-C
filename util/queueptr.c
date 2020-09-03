#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "queueptr.h"

#define DEBUG

static struct quelem *elmalloc(void)
{
    return (struct quelem *)malloc(sizeof(struct quelem));
}

struct queue *quealloc(void)
{
    struct queue *que = (struct queue *)malloc(sizeof(struct queue));
    que->head = que->tail = NULL;
    return que;
}

bool emptyque(struct queue *que)
{
    return que->head == NULL;
}

struct queue *enque(struct queue *que, int val)
{
    struct quelem *elemptr = elmalloc();
    elemptr->val = val;
    elemptr->prev = NULL;

    if(emptyque(que))
        que->head = que->tail = elemptr;
    else
    {
        que->tail->prev = elemptr;
        que->tail = elemptr;
    }
    return que;
}

int first(struct queue *que)
{
    if(!emptyque(que))
        return que->head->val;
    else
    {
        printf("Kolejka pusta\n");
        return 0;
    }
}

int deque(struct queue *que)
{
    if(!emptyque(que))
    {
        struct quelem *tmp = que->head;
        int val = tmp->val;
        que->head = que->head->prev;
        free(tmp);
        return val;
    }
    else
    {
        printf("Kolejka pusta\n");
        return 0;
    }
}

void printque(struct queue *que)
{
    struct quelem *elem;
    for(elem = que->head; elem; elem = elem->prev)
        printf("%d ", elem->val);
    printf("\n");     
}

#ifdef DEBUG
int main(void)
{
    struct queue *que = quealloc();
    int num = 0;
    int c = 0;
    while((c = getchar()) != EOF)
    {
        switch (c)
        {
            case 'a':
                scanf("%i", &num);
                que = enque(que, num);
                break;
            case 'd':
                printf("%d\n", deque(que));
                break;
            case 'f':
                printf("%d\n", first(que));
                break;
            case 'e':
                printf("%d\n", emptyque(que));
                break;
            case 'p':
                printque(que);
                break;
            default:
                break;
        }
    }
    free(que);
    return 0;
}
#endif
