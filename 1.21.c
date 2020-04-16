/*
Ćwiczenie 1.20. Napisz program entab, który zastąpi ciągi znaków odstępu przez
minimalną liczbę znaków tabulacji i znaków odstępu tak, aby odstępy zostały
zachowane. Użyj tych samych punktów tabulacyjnych, co w programie detab.
Jeśli zarówno znak tabulacji, jak i jeden znak odstępu wystarczy do osiągnięcia
punktu tabulacyjnego, to który z nich powinien mieć pierwszeństwo.
*/
#include <stdio.h>

#define TABSIZE 8

int main()
{
    int c, pos, ns, nt;
    ns = nt = 0;
    pos = 1;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            if (pos % TABSIZE != 0)
                ++ns;
            else
            {
                ns = 0;
                ++nt;
            }
        }
        else
        {
            while (nt > 0)
            {
                putchar('\t');
                --nt;
            }
            if (c == '\t')
                ns = 0;
            else
                while (ns > 0)
                {
                    putchar(' ');
                    --ns;
                }
            putchar(c);
            if (c == '\n')
                pos = 1;
            else if (c == '\t')
                pos = pos + (TABSIZE - (pos - 1) % TABSIZE) - 1;
        }
        ++pos;
    }
    return 0;
}