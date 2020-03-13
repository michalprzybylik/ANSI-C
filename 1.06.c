/*
Ćwiczenie 1.6. Sprawdź, że wyrażenie getchar() != EOF może mieć wartość
0 lub 1.
*/
#include <stdio.h>

int main()
{
    int c;
    while ((c = (getchar() != EOF)))
        printf("%d", c);
    printf("%d/n", c);
    return 0;
}