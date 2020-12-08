/*
Ćwiczenie 7.5. Napisz na nowo program kalkulatora przyrostkowego z rozdz. 4, 
stosując funkcję scanf i być może funkcję sscanf do wczytywania i przekształcania 
liczb.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define FUN 'F'
#define VARNR 26

int getop(double *nop, char *sop);
void push(double f);
double pop(void);
double top(void);
void swap(void);
void clear(void);
void dstack(void);
void fun(char s[]);
double inv(double f);

int main(void)
{
    int type, var;
    double nop ,op2, lastval = 0.0;
    char sop[MAXOP];
    double vars[VARNR];
    for (int i = 0; i < VARNR; ++i)
        vars[i] = 0.0;

    while ((type = getop(&nop, sop)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(nop);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("Blad: dzielenie przez 0\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("Blad: dzielenie przez 0\n");
            break;
        case '\n':
            printf("\t%.8g\n", lastval = pop());
            break;
        case '?':
            printf("\t%.8g\n", top());
            break;
        case 'C':
            clear();
            break;
        case 'S':
            swap();
            break;
        case 'D':
            dstack();
            break;
        case FUN:
            fun(sop);
            break;
        case '=':
            pop();
            if (islower(var))
                vars[var - 'a'] = top();
            else
                printf("Blad: brak nazwy zmiennej\n");
            break;
        default:
            if (islower(type))
                push(vars[type - 'a']);
            else if (type == 'V')
                push(lastval);
            else
                printf("Blad: nieznane polecenie %s\n", sop);
            break;
        }
        var = type;
    }
    return 0;
}

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

void fun(char s[])
{
    double op;
    if (!strcmp(s, "sin"))
        push(sin(pop()));
    else if (!strcmp(s, "cos"))
        push(cos(pop()));
    else if (!strcmp(s, "tan"))
        push(tan(pop()));
    else if (!strcmp(s, "ln"))
        push(log(pop()));
    else if (!strcmp(s, "log"))
        push(log10(pop()));
    else if (!strcmp(s, "log"))
        push(log10(pop()));
    else if (!strcmp(s, "pow"))
    {
        op = pop();
        push(pow(pop(), op));
    }
    else if (!strcmp(s, "sqrt"))
        push(sqrt(pop()));
    else if (!strcmp(s, "ceil"))
        push(ceil(pop()));
    else if (!strcmp(s, "floor"))
        push(floor(pop()));
    else if (!strcmp(s, "abs"))
        push(fabs(pop()));
    else if (!strcmp(s, "inv"))
        push(inv(pop()));
    else
        printf("Blad: brak implementacji funkcji %s\n", s);
}

double inv(double f)
{
    return -f;
}

#include <ctype.h>

int getop(double *nop, char *sop)
{
    char c;

    while(isblank(c = getchar()))
        ;
    if (c == EOF || c == '\n')
        return c;
    ungetc(c, stdin);
    if (scanf("%lf", nop))
        return NUMBER;
    if (scanf("%s", sop))
    {
        if (strlen(sop) == 1)
            return sop[0];
        else 
            return FUN;
    }
    return EOF;
}