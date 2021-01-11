/*
Ćwiczenie 7.9. Funkcje podobne do isupper można zrealizować tak, aby oszczędzały 
pamięć albo oszczędzały czas. Zbadaj obie możliwości.
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NTEST 1000000000L

#define macisupper(c) ('A' <= (c) && (c) <= 'Z')

int funisupper(char c)
{
    return 'A' <= c && c <= 'Z';
}

int main(void)
{
    time_t time;

    printf("%ld-krotne wykonanie makra isupper:\n", NTEST);
    time = clock();
    for (int i = 0; i < NTEST; i++)
        macisupper('A');
    printf("czas: %ld\n", clock() - time);

    printf("%ld-krotne wykonanie funkcji isupper:\n", NTEST);
    time = clock();
    for (int i = 0; i < NTEST; i++)
        funisupper('A');
    printf("czas: %ld\n", clock() - time);
    return 0;
}