/*
Zadanie 6.01. Nasza wersja funkcji getword nie obsługuje poprawnie znaków 
podkreślenia, stałych napisowych, komentarzy oraz instrukcji preprocesora. 
Napisz lepszą wersję tej funkcji.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXWORD 128
#define NKEYS (sizeof keytab / sizeof keytab[0]) 

struct key
{
    char *word;
    int count;
};

struct key keytab[] =
    {
        {"auto", 0},
        {"break", 0},
        {"case", 0},
        {"char", 0},
        {"const", 0},
        {"continue", 0},
        {"default", 0},
        {"do", 0},
        {"double", 0},
        {"else", 0},
        {"enum", 0},
        {"extern", 0},
        {"float", 0},
        {"for", 0},
        {"goto", 0},
        {"if", 0},
        {"int", 0},
        {"long", 0},
        {"register", 0},
        {"return", 0},
        {"short", 0},
        {"signed", 0},
        {"sizeof", 0},
        {"static", 0},
        {"struct", 0},
        {"switch", 0},
        {"typedef", 0},
        {"union", 0},
        {"unsigned", 0},
        {"void", 0},
        {"volatile", 0},
        {"while", 0}
    };

int getword(char *word, int lim);
int binsearch(char *s, struct key tab[], int n);

int main(void)
{
    int idx = 0;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF)
        if(isalpha(word[0]))
            if((idx = binsearch(word, keytab, NKEYS)) > 1)
                ++keytab[idx].count;
    for(int i = 0; i < NKEYS; ++i)
        if (keytab[i].count > 0)
            printf("%4d %s\n", keytab[i].count, keytab[i].word);
    return 0;
}

int binsearch(char *s, struct key tab[], int n)
{
    int low = 0, high = n - 1, mid;
    while(low <= high)
    {
        int comp = 0;
        mid = (low + high) / 2;
        if((comp = strcmp(s, tab[mid].word)) < 0)
            high = mid - 1;
        else if (comp > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int getword(char *word, int lim)
{
    int c = 0, d = 0;
    char *w = word;

    while(isspace(c = getchar()))
        ;
    if(c != EOF)
        *w++ = c;
    if(isalpha(c) || c == '_' || c == '#')
    {
        for(; --lim > 0; w++)
            if(!isalnum(*w = getchar()) && *w != '_')
            {
                ungetc(*w, stdin);
                break;
            }
        *w = '\0';
        return word[0];
    }
    if( c == '\'' || c == '"')
    {
        for(; --lim > 0; w++)
            if((*w = getchar()) == '\\')
                *++w = getchar();
            else if (*w == c)
            {
                ++w;
                break;
            }
            else if (*w == EOF)
                break;
    }
    if (c == '/')
    {
        if ((d = getchar()) == '/')
        {
            while(getchar() != '\n')
                ;
        }
        if (d == '*')
        {
            while((c = getchar()) != EOF)
                if(c == '*')
                {
                    if((c = getchar()) == '/')
                        break;
                    else
                        ungetc(c, stdin);
                }
        }
        else
            ungetc(d, stdin);
    }
    *w = '\0';
    return c;
}