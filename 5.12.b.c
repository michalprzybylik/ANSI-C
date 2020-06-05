/*
Ćwiczenie 5.12. Rozbuduj programy entab i detab, aby akceptowały skrót 
    entab -m +n
oznaczający punkty tabulacyjne co n kolumn, poczynając od kolumny m. Wybierz 
dogodny (dla użytkownika) sposób postępowania programu w przypadku 
niekompletnej listy argumentów.
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
    int i, pos = 0, inc = TABINC;
    while (--argc > 0 && ((*++argv)[0] ==  '-' || (*argv)[0] ==  '+'))
        if ((*argv)[0] == '-')
            pos = atoi(*argv + 1);
        else if ((*argv)[0] == '+')
            inc = atoi(*argv + 1);
    for (i = 1; i <= MAXLINE; i++)
        tab[i] = 0;
    if (argc == 0)
        for (i = pos; i <= MAXLINE; i += inc)
                tab[i] = 1;
    else
        while (argc--)
        {
            pos = atoi(*argv++);
            if (pos > 0 && pos <= MAXLINE)
                tab[pos] = 1;
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