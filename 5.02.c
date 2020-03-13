/*
Ćwiczenie 5.2. Napisz funkcję getfloat - zmiennopozycyjny odpowiednik funkcji
getint. Jakiego typu wartość powinna zwracać getfloat jako swoją wartość
funkcyjną?
*/
#include <stdio.h>
#include <ctype.h>
#include "util/getch.h"
#define SIZE 100

int main(void)
{
    int n, getfloat(float *pn), c;
    float array[SIZE] = {0.0};
    for (n = 0; (c = getfloat(&array[n])) && c != EOF; n++)
        printf("%g\n", array[n]);
    return 0;
}

int getfloat(float *pn)
{
    int sign, c;
    float i;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    if (c == '.')
        c = getch();
    for (i = 1; isdigit(c); c = getch())
        *pn = *pn + (i /= 10) * (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}