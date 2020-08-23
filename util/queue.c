#include <stdbool.h>

#define QUEUESIZE 1000

static int queue[QUEUESIZE];
static int *front = queue;
static int *back = queue;

void clear(void)
{
    front = back;
}

void enque(int n)
{
    if (queue + (back - queue + 1) % QUEUESIZE != front)
    {
        back = queue + (back - queue + 1) % QUEUESIZE;
        *back = n;
    }
    else
        printf("Blad: kolejka pelna; nie mozna umiescic %d\n", n);
}

int deque(void)
{
    if (front != back)
    {
        front = queue + (front - queue + 1) % QUEUESIZE;
        return *front;
    }
    else
    {
        printf("Blad: kolejka pusta\n");
        return 0;
    }
}

bool isempty(void)
{
    return front == back;
}

int size(void)
{
    return ((back - queue) - (front - queue) + QUEUESIZE) % QUEUESIZE;
}

void prtque(void)
{
    int *i = front + 1;
    int *j = back;
    while (i != j + 1)
    {
        printf("%d ", *i);
        if (i - queue >= QUEUESIZE)
            i = queue;
        ++i;
    }
    printf("\n");
}