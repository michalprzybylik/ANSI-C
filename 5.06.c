/*
Ćwiczenie 5.6. Napisz na nowo odpowiednie programy i ćwiczenia z poprzednich 
rodziałów, stosując w nich wskaźniki zamiast indeksowania tablic. Interesujące
możliwości są zawarte w funkcjach getline (rozdz. 1 i 4), atoi, itoa i ich wariantach
(rozdz. 2, 3 i 4), reverse (rozdz. 3) oraz strindex i getop (rozdz. 4).
*/
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1024

int mygetline(char *s, int lim);
int atoi1(char *s);
int atoi2(char *s);
void itoa1(int n, char *s);
void itoa2(int n, char *s, int m);
void reverse(char *s);
int strindex(char *s, char *t);
int getch(void);
void ungetch(int c);
void ungets(char *s);
int getop(char *s);

char s[MAXLINE];
char struint[MAXLINE] = "1234";
char strsint[MAXLINE] = "-1234";
int a = 123;
int b = -123;

int main(void)
{
    mygetline(s, MAXLINE);
    printf("%d\n", atoi1(struint));
    printf("%d\n", atoi2(strsint));
    itoa1(a, struint);
    printf("%s\n", struint);
    itoa2(b, strsint, 10);
    printf("%s\n", strsint);
    reverse(s);
    printf("%s\n", s);
    printf("%d\n", strindex("test", "st"));
    return 0;
}

int mygetline(char *s, int lim)
{
    int c;
    char *p = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - p;
}

int atoi1(char *s)
{
    int n;
    for (n = 0; *s >= '0' && *s <= '9'; s++)
        n = 10 * n + (*s - '0');
    return n;
}

int atoi2(char *s)
{
    int sign, n;
    while (isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

void itoa1(int n, char *s)
{
    int sign;
    char *p = s;
    if ((sign = n < 0))
        n = -n;
    do
    {
        *s++ = n % 10 + '0';
    } while (n /= 10);
    if (sign)
        *s++ = '-';
    *s = '\0';
    reverse(p);
}

void itoa2(int n, char *s, int m)
{
    int sign;
    char *p = s;
    if ((sign = n < 0))
        n = -n;
    do
    {
        *s++ = n % 10 + '0';
    } while (n /= 10);
    if (sign)
        *s++ = '-';
    while (s - p < m)
        *s++ = ' ';
    *s = '\0';
    reverse(p);
}

void reverse(char *s)
{
    char c, *f, *b;
    for (b = s; *b; b++)
        ;
    for (f = s, --b; f < b; f++, b--)
        c = *f, *f = *b, *b = c;
}

int strindex(char *s, char *t)
{
    char *bs = s;
    char *ps, *pt;
    for (; *s; s++)
    {
        for (ps = s, pt = t; *pt && *pt == *ps; ps++, pt++)
            ;
        if (pt - t && !*pt)
            return s - bs;
    }
    return -1;
}

#define BUFSIZE 100

int buf[BUFSIZE];
int *bufp = buf;

int getch(void)
{
    return (bufp > 0) ? *--bufp : getchar();
}

void ungetch(int c)
{
    if (buf - bufp >= BUFSIZE)
        printf("Blad: ungetch za wiele zwrotow\n");
    else
        *bufp++ = c;
}

void ungets(char *s)
{
    int len = strlen(s);
    while (len > 0)
        ungetch(*--s);
}

#define NUMBER '0'
#define FUN 'F'

int getop(char *s)
{
    char *ps = s;
    int c;
    while ((*ps = c = getch()) == ' ' || c == '\t')
        ;
    *(ps + 1) = '\0';
    if (islower(c))
    {
        while (islower(*++ps = c = getch()))
            ;
        *ps = '\0';
        if (c != EOF)
            ungetch(c);
        if (strlen(s) > 1)
            return FUN;
        else
            return *s;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    if (c == '-')
    {
        if (isdigit(c = getch()) || c == '.')
            *++ps = c;
        else
        {
            if (c != EOF)
                ungetch(c);
            return '-';
        }
    }
    if (isdigit(c))
        while (isdigit(*++ps = c = getch()))
            ;
    if (c == '.')
        while (isdigit(*++ps = c = getch()))
            ;
    *ps = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}