/*
Ćwiczenie 5.4. Napisz funkcję strend(s,t), która zwraca 1, jeśli tekst z t wwystępuje
na końcu tekstu w s; w przeciwnym przypadku zwraca 0.
*/
#include <stdio.h>

char *s = "test";
char *t = "";

int strend(char *s, char *t);

int main(void)
{
    printf("%d\n", strend(s, t));
    return 0;
}

int strend(char *s, char *t)
{
    char *ps = s, *pt = t;
    while (*ps)
        ++ps;
    while (*pt)
        ++pt;
    for (;ps >= s && pt >= t && *ps == *pt; --ps, --pt)
        if (pt == t)
            return 1;
    return 0;
}
