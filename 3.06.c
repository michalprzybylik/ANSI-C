/*
Ćwiczenie 3.6. Napisz inną wersję funkcji itoa tak, aby akceptowała nie dwa, 
a trzy argumenty. Niech trzeci argument określa minimalny rozmiar pola; jeśli 
przekształcona liczba będzie za krótka, to należy ją uzupełnić z lewej strony 
znakami odstępu.
*/
#include <stdio.h>
#define STRLEN 1024

int abs(int n);
void reverse(char s[]);
void itoa(int n, char s[], int m);

int main()
{
    char str[STRLEN];
    itoa(-12234, str, 5);
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
    while (s[b])
        b++;
    --b;
    for (; f < b; ++f, --b)
        tmp = s[f], s[f] = s[b], s[b] = tmp;
}

void itoa(int n, char s[], int m)
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
    while (i < m)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}