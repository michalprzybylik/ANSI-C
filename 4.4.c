#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double f);
double pop(void);
double top(void);
void swap(void);
void clear(void);
void dstack(void);
double primitive_mod(double a, double b);

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
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
            printf("\t%.8g\n", pop());
            break;
        case '?':
            printf("\t%.8g\n", top());
            break;
        case 'c':
            clear();
            break;
        case 's':
            swap();
            break;
        case 'd':
            dstack();
            break;
        default:
            printf("Blad: nieznane polecenie %s\n", s);
            break;
        }
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

void dstack(void)
{
    double top;
    top = pop();
    push(top);
    push(top);
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
        printf("Blad: Na stosie znajduje sie za malo zmiennych\n");
}

void clear(void)
{
    sp = 0;
}

double primitive_mod(double a, double b)
{
    if (a >= 0 && b > 0)
    {
        while (a > b)
            a -= b;
        return a;
    }
    else if (a < 0 && b < 0)
    {
        while (a < b)
            a -= b;
        return a;
    }
    else if (a >= 0 && b < 0)
    {
        while (a > 0)
            a += b;
        return a;
    }
    else if (a < 0 && b > 0)
    {
        while (a < 0)
            a += b;
        return a;
    }
    else
        return -1;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-')
    {
        if (isdigit(c = getch()) || c == '.')
            s[++i] = c;
        else
        {
            if (c != EOF)
                ungetch(c);
            return '-';
        }
    }
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("Blad: ungetch za wiele zwrotow\n");
    else
        buf[bufp++] = c;
}
