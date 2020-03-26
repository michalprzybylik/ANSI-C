/*
Ćwiczenie 1.8. Napisz program zliczający znaki odstępu, tabulacji i nowego wiersza.
*/
#include <stdio.h>

int main()
{
    int c;
    long ns = 0, nt = 0, nl = 0;
    while (((c = getchar()) != EOF))
    {
        if (c == ' ')
            ++ns;
        if (c == '\t')
            ++nt;
        if (c == '\n')
            ++nl;
    }
    printf("%5ld spaces.\n", ns);
    printf("%5ld tabs.\n", nt);
    printf("%5ld new lines.\n", nl);
    return 0;
}