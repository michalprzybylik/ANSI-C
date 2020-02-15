#include <stdio.h>
#define STRLEN 1024

int abs(int n);
void reverse(char s[]);
void itob(int n, char s[], int b);

int main()
{
    char str[STRLEN];
    itob(-0XA1, str, 16);
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

void itob(int n, char s[], int b)
{
    int i, d, sign;
    sign = (n < 0);
    i = 0;
    do
    {
        d = abs(n % b);
        s[i++] = d < 10 ? d + '0' : d - 10 + 'A';
    } while (n /= b);
    if (sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}