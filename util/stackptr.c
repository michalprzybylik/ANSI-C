#include <stdio.h>

#define MAXVAL 100

static double val[MAXVAL];
static double *sp = val;

void push(double f)
{
    if (sp - val < MAXVAL)
        *sp++ = f;
    else
        printf("Blad: pelen stos; nie mozna umiescic %g\n", f);
}

double pop(void)
{
    if (sp > val)
        return *--sp;
    else
    {
        printf("Blad: pusty stos\n");
        return 0.0;
    }
}

double top(void)
{
    if (sp > val)
        return *(sp - 1);
    else
    {
        printf("Blad: pusty stos\n");
        return 0.0;
    }
}

void swap(void)
{
    if (sp > val + 1)
    {
        double *tmp;
        *tmp = *(sp - 1);
        *(sp - 1) = *(sp - 2);
        *(sp - 2) = *tmp;
    }
    else
    {
        printf("Blad: Na stosie znajduje sie za malo zmiennych\n");
    }
}

void dstack(void)
{
    if (sp > val)
    {
        if (sp - val < MAXVAL)
            *sp++ = *(sp - 1);
        else
            printf("Blad: pelen stos; nie mozna umiescic %g\n", val[sp - 1]);
    }
    else
        printf("Blad: pusty stos\n");
}

void clear(void)
{
    sp = val;
}

int nstack(void)
{
    return sp - val;
}
