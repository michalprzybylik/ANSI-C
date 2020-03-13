/*
Ćwiczenie 5.1. Tak jak została napisana, funkcja getint traktuje znaki + i -, po 
których nie następuje cyfra, jako poprawne reprezentacje zera. Zmień tę funkcję 
tak, aby oddawała je z powrotem na wejście.
*/
#include <stdio.h>
#include <ctype.h>
#include "util/getch.h"
#define SIZE 100

int main(void)
{
    int n, array[SIZE] = {0}, getint(int *pn), c;
    for (n = 0; (c = getint(&array[n])) && c != EOF; n++)
        printf("%d\n", array[n]);
    return 0;
}

int getint(int *pn)
{
    int sign, c, d;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        d = c;
        c = getchar();
        if (!isdigit(c))
        {
            if (c != EOF)
                ungetch(c);
            ungetch(d);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}