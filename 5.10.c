/*
Ćwiczenie 5.10. Napisz program expr obliczający wartość wyrażenia w Odwrotnej
Notacji Polskiej, podanego w poleceniu wywołania programu: każdy operator
lub operand jest oddzielnym argumentem wywołania. Na przykład polecenie

expr 2 3 4 + *

oblicza wartość 2x(3+4).
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUM '0'
#define FUN 'F'
#define OP 'O'
#define ERR 'E'

char checkop(char *s);
void push(double f);
double pop(void);
double top(void);
void fun(char *s);
double inv(double f);

int main(int argc, char *argv[])
{
    double op2;
    while (--argc > 0)
    {
        switch (checkop(*++argv))
        {
        case NUM:
            push(atof(*argv));
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
            {
                printf("Blad: dzielenie przez 0\n");
                argc = 1;
            }
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
            {
                printf("Blad: dzielenie przez 0\n");
                argc = 1;
            }
            break;
        case '^':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case FUN:
            fun(*argv);
            break;
        default:
            printf("Blad: niepoprawny operator %s\n", *argv);
            argc = 1;
            break;
        }
    }
    printf("%f\n", pop());
    return 0;
}

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

void fun(char *s)
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
    else if (!strcmp(s, "log10"))
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

char checkop(char *s)
{
    if (islower(*s))
        return FUN;
    if (!isdigit(*s) && *s != '.' && *s != '-' && *(s + 1) == '\0')
        return *s;
    if (*s++ == '-' && *s == '\0')
        return '-';
    while (isdigit(*s))
        s++;
    if (*s == '.')
    {
        s++;
        while (isdigit(*s))
            s++;
    }
    if (*s == '\0')
        return NUM;
    return ERR;
}