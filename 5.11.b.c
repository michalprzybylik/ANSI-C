/*
Ćwiczenie 5.11. Zmień programy entab i detab (napisane jako ćwiczenia w rozdz. 1) tak, aby 
argumentami ich wywołania mogły być listy punktów tabulacyjnych. Zastosuj
domyślne punkty tabulacyjne, jeśli nie podano argumentów.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define TABINC 8

void settab(int argc, char *argv[], char *tab);
void detab(char *tab);

int main(int argc, char *argv[])
{
    char tab[MAXLINE + 1];
    settab(argc, argv, tab);
    detab(tab);
    return 0;
}

void settab(int argc, char *argv[], char *tab)
{
    int i, pos;

    if (argc <= 1)
        for (i = 1; i <= MAXLINE; i++)
            if (i % TABINC == 0)
                tab[i] = 1;
            else
                tab[i] = 0;
    else
    {
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = 0;
        while (--argc > 0)
        {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAXLINE)
                tab[pos] = 1;
        }
    }
}

void detab(char *tab)
{
    int c, pos = 1;

    while ((c = getchar()) != EOF)
        ;
    if (c == '\t')
        do
            putchar(' ');
        while (pos <= MAXLINE && !tab[pos]);
    else if (c == '\n')
    {
        putchar(c);
        pos = 1;
    }
    else
    {
        putchar(c);
        ++pos;
    }
}