/*
Ćwiczenie 5.3. Napisz wskaźnikową wersję funkcji strcat opisanej w rozdz 2:
funkcja strcat(s,t) dopisuje tekst z t na koniec tekstu w s.
*/
#include <stdio.h>

void mystrcat(char *s, char *t);

char stra[] = "testa";
char strb[] = "testb";

int main(void)
{
    mystrcat(stra, strb);
    printf("%s\n", stra);
    return 0;
}

void mystrcat(char *s, char *t)
{
    while (*s)
        s++;
    while ((*s++ = *t++))
        ;
}