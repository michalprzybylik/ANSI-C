#include<stdio.h>

#define ARRAYSIZE (125 - 32 + 1) 
#define HISTSIZE 50

int main()
{
    int c, nc = 0, max = 0, currentsize = 0;
    int tab[ARRAYSIZE];

    for(int i = 0; i < ARRAYSIZE; ++i)
        tab[i] = 0;

    while (((c = getchar()) != EOF ))
            ++tab[c - ' '];

    for(int i = 0; i < ARRAYSIZE; ++i)
        if(max < tab[i])
            max = tab[i];

    if(max > 0)
    {
        printf("ZNAK\n");
        for (int i = 0; i < ARRAYSIZE; ++i)
        {
            printf("%4c |", i + ' ' );
            currentsize = ( tab[i] * 1.0 / max * 1.0 ) * HISTSIZE;
            for(int j = 0; j < HISTSIZE; ++j)
            {
                if (j < currentsize)
                    putchar('*');
                else
                    putchar(' ');
            }
            printf(" %5d WYSTAPIEN", tab[i]);
            putchar('\n');
        }
    }
    else
        printf("NIE WPROWADZONO ZADNYCH ZNAKOW\n");
    return 0;
}