/*
Zadanie 5.20. Rozszerz możliwości programu dcl o obsługę typów argumentów 
funkcji, o rozpoznawanie kwalifikatorów takich jak const itp.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXTOKEN 1024
#define MAXOUT 1024 * 1024

enum
{
    NAME,
    PARENS,
    BRACKETS
};

void errmsg(char *msg);
void dcl(void);
void dirdcl(void);
int gettoken(void);
void clrerr(void);
int strcomp(char **s, char **t);
bool istypequal(char *s);
bool istypespec(char *s);
void dclspec(void);
void paramdcl(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUT];
bool err = false;
bool prevspec = false;
bool prevtoken = false;
bool aftdec;

int main(void)
{
    while (gettoken() != EOF)
    {
        aftdec = false;
        if (tokentype == '\n')
            continue;
        if (istypequal(token))
        {
            prevspec = true;
            strcpy(datatype, token);
            continue;
        }
        if (prevspec)
        {
            strcat(datatype, " ");
            strcat(datatype, token);
            prevspec = false;
        }
        else
            strcpy(datatype, token);
            aftdec = true;
        out[0] = '\0';
        dcl();
        if (err || tokentype != '\n')
        {
            errmsg("blad skladniowy\n");
            clrerr();
        }
        else
        {
            printf("%s: %s %s\n", name, out, datatype);
            name[0] = out[0] = datatype[0] = '\0';
        }
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
        if (err)
            return; 
        if (tokentype != ')')
        {
            errmsg("blad: brak nawiasu )\n");
            return;
        }
    }
    else if (tokentype == NAME)
    {
        if (name[0] == '\0')
            strcpy(name, token);
    }
    else if (aftdec)
        prevtoken = true;
    else
    {
        errmsg("blad: spodziewana nazwa lub (deklarator)\n");
        return;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " funkcja zwracajaca");
        else if (type == '(')
        {
            strcat(out, " funkcja oczekujaca");
            paramdcl();
            if (err)
                return; 
            strcat(out, " i zwracajaca");
        }
        else
        {
            strcat(out, " tablica");
            strcat(out, token);
            strcat(out, " o elementach");
        }
}

void dclspec(void)
{
    char temp[MAXTOKEN];
    temp[0] = '\0';
    gettoken();
    do
    {
        if (err)
            return;
        if (tokentype != NAME)
        {
            prevtoken = true;
            dcl();
            if (err)
                return;
        }
        else if (istypespec(token) || istypequal(token))
        {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else
        {
            errmsg("nieznany typ parametru\n");
            return;
        }
    } while (tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ",");
}

void paramdcl(void)
{
    if (err)
        return;
    do
    {
        dclspec();
        if (err)
            return;
    } while (tokentype == ',');
    if (tokentype != ')')
    {
        errmsg("brakujący nawias ')' w deklaracji parametru\n");
        return;
    }
}

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int c);
    char *p = token;

    if (prevtoken)
    {
        prevtoken = false;
        return tokentype;
    }
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
    if (tokentype != '\n') 
        while(getch() != '\n')
            ;
}

int strcomp(char **s, char **t)
{
    return strcmp(*s, *t);
}

bool istypequal(char *s)
{
    static char *typesqual[] =
        {
            "const",
            "register",
            "static",
            "volatile"
        };
    char **result = (char **)bsearch(&s, typesqual, sizeof(typesqual) / sizeof(typesqual[0]),
                                     sizeof(char *), (int (*)(const void *, const void *))strcomp);
    return result != NULL;
}

bool istypespec(char *s)
{
    static char *types[] =
        {
            "bool",
            "char",
            "double",
            "float",
            "int",
            "long",
            "short",
            "signed",
            "unsigned",
            "void",
        };
    char **result = (char **)bsearch(&s, types, sizeof(types) / sizeof(types[0]),
                                     sizeof(char *), (int (*)(const void *, const void *))strcomp);
    return result != NULL;
}