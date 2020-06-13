/*
Zadanie 5.18. Uodpornij program dcl na błędy w danych wejściowych.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXTOKEN 1024
#define MAXOUT 1024 * 1024

enum
{
    NAME,
    PARENS,
    BRACKETS
};

bool err = false;
void errmsg(char *msg);
void dcl(void);
void dirdcl(void);
int gettoken(void);
void clrerr(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUT];

int main(void)
{
    while (gettoken() != EOF)
    {
        if (tokentype == '\n')
            continue;
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (err || tokentype != '\n')
        {
            errmsg("blad skladniowy\n");
            clrerr();
        }
        else
            printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void)
{
    int ns;

    if (err)
        return;
    for (ns = 0; gettoken() == '*';)
        ++ns;
    dirdcl();
    if (err)
        return;   
    while (ns-- > 0)
        strcat(out, " wskaznik do");
}

void dirdcl(void)
{
    int type;

    if (err)
        return;
    if (tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
        {
            errmsg("blad: brak nawiasu )\n");
            return;
        }
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
    {
        errmsg("blad: spodziewana nazwa lub (deklarator)\n");
        return;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " funkcja zwracajaca");
        else
        {
            strcat(out, " tablica");
            strcat(out, token);
            strcat(out, " o elementach");
        }
}

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int c);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c) || c == '_')
    {
        for (*p++ = c; isalnum(c = getch()) || c == '_';)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

#define BUFSIZE 128

static int buf[BUFSIZE];
static int *bufp = buf;

int getch(void)
{
    return (bufp - buf > 0) ? *--bufp : getchar();
}

void ungetch(int c)
{
    if (bufp - buf >= BUFSIZE)
        printf("Blad: ungetch za wiele zwrotow\n");
    else
        *bufp++ = c;
}

void errmsg(char *msg)
{
    printf("%s", msg);
    err = true;
}

void clrerr(void)
{
    err = false;
}