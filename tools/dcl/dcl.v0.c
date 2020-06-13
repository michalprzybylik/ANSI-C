#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 1024
#define MAXOUT 1024 * 1024

enum
{
    NAME,
    PARENS,
    BRACKETS
};

void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUT];

int main(void)
{
    while (gettoken() != EOF)
    {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("blad skladniowy\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';)
        ++ns;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " wskaznik do");
}

void dirdcl(void)
{
    int type;

    if (tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
            printf("blad: brak nawiasu )\n");
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("blad: spodziewana nazwa lub (deklarator)\n");
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
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch());)
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
        printf("Blad: ungetch zűa wiele zwrotow\n");
    else
        *bufp++ = c;
}