#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("Blad: ungetch za wiele zwrotow\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[])
{
    int len = strlen(s);
    while(len > 0)
        ungetch(s[--len]);
}