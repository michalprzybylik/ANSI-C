#include<stdio.h>

#define MAXWORD 20
#define HISTSIZE 50

int main()
{
    int c, nc = 0, max = 0, currentsize = 0;
    int tab[MAXWORD];

    for(int i = 0; i < MAXWORD; ++i)
        tab[i]=0;

    while (((c = getchar()) != EOF ))
    {
        if( c == ' ' || c == '\t' || c == '\n')
        {
            if(nc > 0)
            {
                if (nc < MAXWORD)
                    ++tab[nc - 1];
                else
                    ++tab[MAXWORD - 1];
                nc = 0;
            }
        }
        else
            ++nc;
    }

    for(int i = 0; i < MAXWORD; ++i)
        if(max < tab[i])
            max = tab[i];

    if(max > 0)
    {
        printf("D. SLOWA\n");
        for (int i = 0; i < MAXWORD; ++i)
        {
            if ( i == 0 )
            
            else if ( i == MAXWORD - 1 )
                printf("    >=20 |");
            else 
                printf("%8d |", i + 1);
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
        printf("NIE WPROWADZONO ZADNYCH SLOW\n");
    return 0;
}