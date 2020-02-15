#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define FUN 'F'
#define VARNR 26

int getop(char s[]);
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
    double op2, lastval = 0.0;
    char s[MAXOP];
    double vars[VARNR];
    for (int i = 0; i < VARNR; ++i)
        vars[i] = 0.0;

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
            fun(s);
            break;
        case '=':
            pop();
            if(islower(var))
                vars[var - 'a'] = top();
            else
                printf("Blad: brak nazwy zmiennej\n");
            break;
        default:
            if(islower(type))
                push(vars[type - 'a']);
            else if (type == 'V')
                push(lastval);
            else
                printf("Blad: nieznane polecenie %s\n", s);
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

int getch(void);
void ungetch(int);
void ungets(char s[]);

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

char buf = -1;

int getch(void)
{
    int c;
    if (buf != -1)
    {
        c = buf;
        buf = -1;
    }
    else
        c = getchar();
    return c;
}

void ungetch(int c)
{
    if (buf != -1)
        printf("Blad: ungetch za wiele zwrotow\n");
    else
        buf = c;
}

void ungets(char s[])
{
    int len = strlen(s);
    while(len > 0)
        ungetch(s[--len]);
}
