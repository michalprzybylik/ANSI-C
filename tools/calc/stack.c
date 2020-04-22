#include <stdio.h>

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Blad: pelen stos; nie mozna umiescic %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("Blad: pusty stos\n");
        return 0.0;
    }
}

double top(void)
{
    if (sp > 0)
        return val[sp - 1];
    else
    {
        printf("Blad: pusty stos\n");
        return 0.0;
    }
}

void swap(void)
{
    double top, next;
    if (sp > 1)
    {
        top = pop();
        next = pop();
        push(top);
        push(next);
    }
    else
    {
        printf("Blad: Na stosie znajduje sie za malo zmiennych\n");
    }
}

void dstack(void)
{
    double top;
    top = pop();
    push(top);
    push(top);
}

void clear(void)
{
    sp = 0;
}
