/*
Zadanie 7.02. Napisz program, który w jakiejś sensownej formie wypisze dowolny 
strumień znaków wejściowych. Program powinien przynajmniej wypisywać 
znaki niegraficzne w postaci ósemkowej lub szesnastkowej (zależnie od miejscowych 
zwyczajów), a także dzielić zbyt długie wiersze.
*/
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 16

int main(void)
{
    char c;
    int len = 0;

    while ((c = getchar()) != EOF)
    {

        if(isgraph(c))
            printf("%4c ", c);
        else
            printf("0x%02x ", c);
        if (++len > MAXLINE)
        {
            len = 0;
            putchar('\n');
        }
    }
    putchar('\n');
    return 0;
}