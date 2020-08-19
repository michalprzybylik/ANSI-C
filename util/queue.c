#include <stdbool.h>

#define QUEUESIZE 1000
static int queue[QUEUESIZE];
static int front = 0;
static int back = 0;

void clear(void)
{
    front = back;
}

void enqueue(int n)
{
    if ((back + 1) % QUEUESIZE != front)
    {
        back = (back + 1) % QUEUESIZE;
        queue[back] = n;
    }
    else
        printf("Blad: kolejka pelna; nie mozna umiescic %d\n", n);
}

int dequeue(void)
{
    if (front != back)
    {
        front = (front + 1) % QUEUESIZE;
        return queue[front];
    }
    else
    {
        printf("Blad: kolejka pusta\n");
        return 0;
    }
}

bool is_empty(void)
{
    return front == back;
}

int size(void)
{
    return (back - front + QUEUESIZE) % QUEUESIZE;
}