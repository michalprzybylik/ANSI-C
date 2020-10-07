#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 10
#define MAXLINE 10

int isnum(char *p);
int getword(char word[], int len);
int ungetword(char word[], int len);

int main(int argc, char *argv[])
{
    int maxword = MAXWORD, maxline = MAXLINE;
    
    if (argc == 2 && isnum(argv[1])) 
    {
        maxline = atoi(argv[1]);
        maxword = maxline; 
        --argc;
    }
    if (argc != 1)
    {
        printf("Blad: Wywolanie fold [dlugosc wiersza]\n");
        return 1;
    }

    char c;
    char *word = (char *)malloc(maxword * sizeof(char) + 1);
    int len = 0;
    int wlen = 0;

    while ((wlen = getword(word, maxword)) != -1)
    {
        if(wlen == 0)
        {
            c = getchar();
            putchar(c);
            len = (c == '\n') ? 0 : len + 1; 
        }
        if (len + wlen > maxline)
        {
            putchar('\n');
            len = 0;
        }
        ungetword(word, maxword);
        len += wlen;
    }
    free(word);
    return 0;
}

int isnum(char *p)
{
    while(isnumber(*p))
        p++;
    return !*p;
}

int getword(char word[], int len)
{
    int c;
    int i = 0;
    while(isalnum(c = getchar()) && i < len)
        word[i++] = c;
    word[i] = '\0';
    if (c == EOF)
        return -1;
    ungetc(c, stdin);
    return i;
}

int ungetword(char word[], int len)
{
    int i = 0;
    while(word[i] && i < len)
        putchar(word[i++]);
    return i;
}