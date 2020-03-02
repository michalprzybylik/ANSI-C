/*
Ćwiczenie 4.12. Zastosuj idee funkcji printd do napisania rekurencyjnej wersji
funkcji itoa, tj. zamieniającej liczbę całkowitą na ciąg cyfr za pomocą wywołania
rekurencyjnego.
*/
#include <stdio.h>
#include <string.h>
#define MAXSTR 256
#define TESTNR 10

int main(void)
{
    void itoa(int n, char s[]);
    char s[MAXSTR];
    int test[TESTNR] = {0, 232, -231, 22342, 2342, -148245, 42579, -73291, 85220, 3857};
    for (int i = 0; i < TESTNR; ++i)
    {
        itoa(test[i], s);
        printf("%s\n", s);
    }
    return 0;
}

void itoa(int n, char s[])
{
    static int i, call;
    ++call;
    if (n < 0)
    {
        s[i++] = '-';
        n = -n;
    }
    if (n / 10)
        itoa(n / 10, s);
    s[i++] = n % 10 + '0';
    s[i] = '\0';
    --call;
    if (!call)
        i = 0;
}
