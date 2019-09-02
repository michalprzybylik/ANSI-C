#include <stdio.h>

void skipQuote(int c);
void skipLineComment();
void skipComment();

#define SEARCH         \
    if (c == '{')      \
        ++brace;       \
    else if (c == '}') \
        --brace;       \
    else if (c == '[') \
        ++brack;       \
    else if (c == ']') \
        --brack;       \
    else if (c == '(') \
        ++paren;       \
    else if (c == ')') \
        --paren;

int main()
{
    int c, brace, brack, paren;
    brace = brack = paren = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '/')
        {
            if ((c = getchar()) == '*')
                skipComment();
            else if (c == '/')
                skipLineComment();
            else
                SEARCH
        }
        else if (c == '\'' || c == '"')
            skipQuote(c);
        else
            SEARCH

        if (brace < 0)
        {
            printf("Blad: Nawiasy klamrowe\n");
            brace = 0;
        }
        else if (brack < 0)
        {
            printf("Blad: Nawiasy kwadratowe\n");
            brace = 0;
        }
        else if (paren < 0)
        {
            printf("Blad: Nawiasy okragle\n");
            paren = 0;
        }
    }
    if (brace != 0)
        printf("Blad: Nawiasy klamrowe\n");
    if (brack != 0)
        printf("Blad: Nawiasy kwadratowe\n");
    if (paren != 0)
        printf("Blad: Nawiasy okragle\n");
    return 0;
}

void skipQuote(int c)
{
    int d;
    while ((d = getchar()) != c)
        if (d == '\\')
            getchar();
}

void skipLineComment()
{
    while ((getchar()) != '\n')
        ;
}

void skipComment()
{
    int c, d;
    c = getchar();
    d = getchar();
    while (c != '*' || d != '/')
    {
        c = d;
        d = getchar();
    }
}
