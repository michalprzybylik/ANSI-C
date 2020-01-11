#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define FUN 'F' //niestandardowy operator

int getop(char s[]);
void push(double f);
double pop(void);
double top(void);
void swap(void);
void clear(void);
void dstack(void);
void fun(char s[]);

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
            fun(s);
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
        return val[sp];
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
    if(!strcmp(s, "sin"))
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
        push(pow(pop(),op));
    }
    else if (!strcmp(s, "sqrt"))
        push(sqrt(pop()));
    else if (!strcmp(s, "ceil"))
        push(ceil(pop()));
    else if (!strcmp(s, "floor"))
        push(floor(pop()));
    else if (!strcmp(s, "abs"))
        push(fabs(pop()));
    else
        printf("Blad: brak implementacji funkcji %s\n", s);
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
    i = 0;
    if (islower(c))
    {
        while (islower(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        if (strlen(s) > 1)
            return FUN;
        else
            return s[0];
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
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