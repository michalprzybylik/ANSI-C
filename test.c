#include <stdio.h>
#include <stdbool.h>

#define QUEUESIZE 1000
static int queue[QUEUESIZE];
static int *front = queue;
static int *back = queue;

void clear(void);
void enqueue(int n);
int dequeue(void);
bool isempty(void);
int size(void);
void prtque(void);

int main(void)
{
    int c = 0;
    int number = 0;
    while((c = getchar()) != EOF)
    {
        switch (c)
        {
            case 'd':
                scanf("%d", &number);
                enqueue(number);
                break;
            case 'u':
                printf("%d\n", dequeue());
                break;
            case 's':
                printf("%d\n", size());
                break;
            case 'e':
                printf("%d\n", isempty());
                break;
            case 'p':
                prtque();
                break;
            default:
                break;
        }
    }
}

void clear(void)
{
    front = back;
}

void enqueue(int n)
{
    if (queue + (back - queue + 1) % QUEUESIZE != front)
    {
        back = queue + (back - queue + 1) % QUEUESIZE;
        *back = n;
    }
    else
        printf("Blad: kolejka pelna; nie mozna umiescic %d\n", n);
}

int dequeue(void)
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