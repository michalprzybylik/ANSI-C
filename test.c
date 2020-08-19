#include <stdio.h>
#include <stdbool.h>

#define QUEUESIZE 1000
static int queue[QUEUESIZE];
static int front = 0;
static int back = 0;

void clear(void);
void enqueue(int n);
int dequeue(void);
bool is_empty(void);
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
                printf("%d\n", is_empty());
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

void prtque(void)
{
    int i = front + 1;
    int j = back;
    while (i != j + 1)
    {
        printf("%d ", queue[i]);
        if (i >= QUEUESIZE)
            i = 0;
        ++i;
    }
    printf("\n");
}