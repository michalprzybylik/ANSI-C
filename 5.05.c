/*
Ćwiczenie 5.5. Napisz własne wersje funkcji bibliotecznych strncpy, strncat oraz
strncmp, które obsługują co najwyżej n początkowych znaków swoich argumentów.
Dla przykładu, funkcja strncpy(s,t,n) kopiuje co najwyżej n znaków
tekstu z t do s. Pełne opisy tych funkcji znajdziesz w dodatku B.
*/
#include <stdio.h>

#define MAXLEN 64

char s[MAXLEN] = "tests";
char t[MAXLEN] = "testt";

void mystrncpy(char *s, char *t, int n);
void mystrncat(char *s, char *t, int n);
int mystrncmp(char *s, char *t, int n);

int main(void)
{
    printf("%s\n", s);
    printf("%s\n", t);
    mystrncpy(s, t, -1);
    printf("%s\n", s);
    printf("%s\n", t);
    mystrncat(s, t, -1);
    printf("%s\n", s);
    printf("%s\n", t);
    printf("%d\n", mystrncmp(s, t, 10));
    return 0;
}

void mystrncpy(char *s, char *t, int n)
{
    for (; n && (*s = *t); s++, t++, n--)
        ;
    *s = '\0';
}

void mystrncat(char *s, char *t, int n)
{
    while (*s)
        s++;
    for (; n && (*s = *t); s++, t++, n--)
        ;
    *s = '\0';
}

int mystrncmp(char *s, char *t, int n)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0' || --n <= 0)
            return 0;
    return *s - *t;
}