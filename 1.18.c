#include<stdio.h>

#define MAXLINE 1000

int getLine(char line[], int lim);
int deleteBlank(char to[], char from[]);

int main()
{
    int len, max = 0;
    char line[MAXLINE];
    char newline[MAXLINE];

    while(getLine(line, MAXLINE) != 0)
    {
        if(deleteBlank(newline, line))
            printf("%s", newline);
    }
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
    if(i < lim)
        line[i] = '\0';
    else
        line[lim - 1] = '\0';   
    return i;
}

int deleteBlank(char to[], char from[])
{
    int i = 0, j = 0;
    while(from[j] == ' ' || from[j] == '\t' || from[j] == '\n')
        ++j;
    while((to[i] = from[i + j]) != '\0' )
        ++i;
    return i;
}