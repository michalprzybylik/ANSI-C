#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

static int buf[BUFSIZE];
static int *bufp = buf;

int getch(void)
{
    return (bufp - buf > 0) ? *--bufp : getchar();
}

void ungetch(int c)
{
    if (buf + BUFSIZE <= bufp)
        printf("Blad: ungetch za wiele zwrotow\n");
    else
        *bufp++ = c;
}

void ungets(char *s)
{
    char *end = s + strlen(s);
    while(s < end)
        ungetch(*--end);
}