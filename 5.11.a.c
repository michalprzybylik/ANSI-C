/*
Ćwiczenie 5.11. Zmień programy entab i detab (napisane jako ćwiczenia w rozdz. 1) tak, aby 
argumentami ich wywołania mogły być listy punktów tabulacyjnych. Zastosuj
domyślne punkty tabulacyjne, jeeli nie podano argumentów.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define TABINC 8

void settab(int argc, char *argv[], char *tab);
void entab(char *tab);

int main(int argc, char *argv[])
{
    char tab[MAXLINE + 1];
    settab(argc, argv, tab);
    entab(tab);
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

void entab(char *tab)
{
    int c, pos, nb, nt;
    nb = nt = 0;

    for (pos = 1; (c = getchar()) != EOF; ++pos)
        if (c == ' ')
        {
            if (pos > MAXLINE || tab[pos])
            {
                nb = 0;
                ++nt;
            }
            else
                ++nb;
        }
        else
        {
            for (; nt > 0; nt--)
                putchar('\t');
            if (c == '\t')
                nb = 0;
            else
                for (; nb > 0; nb--)
                    putchar(' ');
            putchar(c);
            if (c == '\n')
                pos = 0;
            else if (c == '\t')
                while (pos < MAXLINE && !tab[pos])
                    ++pos;
        }
}