/*
Ćwiczenie 1.20. Napisz program detab zastępujący znaki tabulacji odpowiednią 
liczbą znaków odstępu, określoną przez następny punkt tabulacyjny. Przyjmij
stały zbiór punktów tabulacyjnych, przypuśćmy co n pozycji. Czy n powinno
być zmienną, czy raczej parametrem symbolicznym. 
*/
#include <stdio.h>

#define TABSIZE 8

int main(void)
{
    int c, pos, toadd;
    while ((c = getchar()) != EOF)
    {
        if (pos > TABSIZE - 1)
            pos = 0;
        if (c == '\t')
        {
            toadd = TABSIZE - pos;
            while (toadd > 0)
            {
                putchar(' ');
                --toadd;
            }
            pos = 0;
        }
        else if (c == '\n')
        {
            putchar(c);
            pos = 0;
        }
        else
        {
            putchar(c);
            ++pos;
        }
    }
    return 0;
}