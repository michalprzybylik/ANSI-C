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

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char out[MAXOUT];

int main(void)
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF)
    {
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*')
            {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            }
            else if (type == NAME)
            {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
                printf("niepoprawdne dane wejściowe: %s\n", token);
            printf("%s\n", out);
    }
    return 0;
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
        printf("Blad: ungetch za wiele zwrotow\n");
    else
        *bufp++ = c;
}