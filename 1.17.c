#include<stdio.h>

#define MAXLINE 1000

int getLine(char line[], int lim);
void copy(char to[], char from[]);

int main()
{
    int len, max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];

    while((len = getLine(line, MAXLINE)) != 0)
        if(len > 80)
            printf("%s", line);
    return 0;
}

int getLine(char line[], int lim)
{
    int i = 0, c = 0;
    for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if(i < lim - 1)
            line[i] = c;
    if(c == '\n')
    {
        if(i < lim - 1)
            line[i] = c;
        ++i;
    }
    if(i < MAXLINE)
        line[i] = '\0';
    else
        line[MAXLINE - 1] = '\0';   
    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while((to[i] = from[i]) != '\0')
        ++i;
}