/*
Ćwiczenie 1.9. Napisz program, który podczas kopiowania wejścia na wyjście zastępuje 
każdy znak tabulacji przez sekwencję znaków \t, każdy znak cofania
przez sekwencję \b oraz każdy znak \ przez dwa takie znaki.
*/
#include <stdio.h>

int main()
{
    int c;
    int ischar;
    while (((c = getchar()) != EOF))
    {
        ischar = 1;
        if (c == '\t')
        {
            putchar('\\');
            putchar('t');
            ischar = 0;
        }
        if (c == '\b')
        {
            putchar('\\');
            putchar('b');
            ischar = 0;
        }
        if (c == '\\')
        {
            putchar('\\');
            putchar('\\');
            ischar = 0;
        }
        if (ischar == 1)
            putchar(c);
    }
    return 0;
}