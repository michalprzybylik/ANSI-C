/*
Ćwiczenie 3.4. W notacji uzupełnieniowej do 2 nasza wersja funkcji itoa nie obsłuży 
największej liczby ujemnej, gdy wartość n jest równa -(2^(rozmiar_slowa - 1)). 
Wyjaśnij, dlaczego. Zmień tę funkcję tak, aby wypisywała poprawną wartość 
liczby niezależnie od maszyny, na której będzie uruchamiana.
*/
#include <stdio.h>
#define STRLEN 1024

int abs(int n);
void reverse(char s[]);
void itoa(int n, char s[]);

int main()
{
    char str[STRLEN];
    itoa(1, str);
    printf("%s\n", str);
    return 0;
}

int abs(int n)
{
    return n >= 0 ? n : -n;
}

void reverse(char s[])
{
    int f, b, tmp;
    f = b = 0;
    while (s[++b])
        ;
    --b;
    for (; f < b; ++f, --b)
        tmp = s[f], s[f] = s[b], s[b] = tmp;
}

void itoa(int n, char s[])
{
    int i, sign;
    sign = (n < 0);
    i = 0;
    do
    {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);
    if (sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}