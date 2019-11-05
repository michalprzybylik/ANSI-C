#include <stdio.h>
#define MAXLINE 1000

int mygetline(char line[], int lim);
int strindex(char source[], char searchfor[]);
int mystrlen(char str[]);
int strrindex(char source[], char searchfor[]);

char pattern[] = "";

int main(void)
{
    char line[MAXLINE];
    unsigned int found = 0;
    int index = 0;

    while (mygetline(line, MAXLINE) > 0)
        if ((index = strrindex(line, pattern)) >= 0)
        {
            printf("%s", line);
            ++found;
        }
    return 0;
}

int mygetline(char line[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return i;
}

int strindex(char source[], char searchfor[])
{
    int i, j, k;

    for (i = 0; source[i] != '\0'; i++)
    {
        for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)
            ;
        if (k > 0 && searchfor[k] == '\0')
            return i;
    }
    return -1;
}

int mystrlen(char str[])
{
    int i = 0;
    while (str[i])
        ++i;
    return i;
}

int strrindex(char source[], char searchfor[])
{
    int i, j, k;

    int sourcelen = mystrlen(source);
    int searchforlen = mystrlen(searchfor);
    for (i = sourcelen - 1; i >= 0; --i)
    {
        for (j = i, k = searchforlen - 1; k >= 0 && source[j] == searchfor[k]; --j, --k)
            ;
        if (k == -1)
            return i + 1 - searchforlen;
    }
    return -1;
}