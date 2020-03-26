/*
Ćwiczenie 1.9. Napisz program, który - przepisując wejście na wyjście - będzie 
zastępować jednym znakiem odstępu każdy ciąg złożony z jednego lun kilku 
takich znaków.
*/
#include <stdio.h>

int main()
{
    int c;
    int isspace = 0;
    while (((c = getchar()) != EOF))
    {
        if (c == ' ')
            isspace = 1;
        if (c != ' ')
        {
            if (isspace == 1)
            {
                putchar(' ');
                isspace = 0;
            }
            putchar(c);
        }
    }
    return 0;
}