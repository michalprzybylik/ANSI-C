#include <stdio.h>

long int htoi(char s[]);

int main()
{
    printf("%ld\n", htoi("-x"));
    printf("%ld\n", htoi("+p1"));
    printf("%ld\n", htoi("+-"));
    printf("%ld\n", htoi("+-1"));
    printf("%ld\n", htoi("+fasdf-"));
    printf("%ld\n", htoi(""));
    printf("%ld\n", htoi("+"));
    printf("%ld\n", htoi("-"));
    printf("%ld\n", htoi("0x"));
    printf("%ld\n", htoi("+0x0"));
    printf("%ld\n", htoi("-0x"));
    printf("%ld\n", htoi("1"));
    printf("%ld\n", htoi("-1"));
    printf("%ld\n", htoi("0x-1"));
    printf("%ld\n", htoi("01"));
    printf("%ld\n", htoi("11"));
    printf("%ld\n", htoi("G"));
    printf("%ld\n", htoi("0X11"));
    printf("%ld\n", htoi("0x11"));
    printf("%ld\n", htoi("0x11aB"));
    printf("%ld\n", htoi("0x11G"));

    return 0;
}

long int htoi(char s[])
{
    int i = 0;
    long int h = 0;
    for (; s[i] != '\0'; ++i)
    {
        if (i == 0 && s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
            i += 2;
        if (s[i] >= '0' && s[i] <= '9')
            h = 16 * h + s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            h = 16 * h + s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            h = 16 * h + s[i] - 'A' + 10;
        else if (s[i] != '\0')
            return -1L;
    }
    return h;
}

//Funkcja z obsluga znakow +- jej wada jest to ze gdy wystepuje blad danych wejsciowych trzeba zwrocic jakac wartosc z zakresu poprawnych wartosci (-1L)
/*
long int htoi(char s[])
{
    int i = 0;
    long int h = 0;
    short sign = 1;
    if (s[0] == '-')
    {
        sign = -1;
        ++i;
    }
    else if (s[0] == '+')
        ++i;
    for (; s[i] != '\0'; ++i)
    {
        if (i < 2 && s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
            i += 2;
        if (s[i] >= '0' && s[i] <= '9')
            h = 16 * h + s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            h = 16 * h + s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            h = 16 * h + s[i] - 'A' + 10;
        else if (s[i] != '\0')
            return -1L;
    }
    return sign * h;
}
*/