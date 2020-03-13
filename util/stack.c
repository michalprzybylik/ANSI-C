#include <stdio.h>

#define MAXVAL 100

static int sp = 0;
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
    if (sp > 1)
    {
        double tmp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = tmp;
    }
    else
    {
        printf("Blad: Na stosie znajduje sie za malo zmiennych\n");
    }
}

void dstack(void)
{
    if (sp > 0)
    {
        if (sp < MAXVAL)
            val[sp++] = val[sp - 1];
        else
            printf("Blad: pelen stos; nie mozna umiescic %g\n", val[sp - 1]);
    }
    else
        printf("Blad: pusty stos\n");
}

void clear(void)
{
    sp = 0;
}

int nstack(void)
{
    return sp;
}
