#include <stdio.h>

#define WORD 'w'
#define COMMENT 'c'
#define STRING 's'

int getword(char *word, int lim)
{
    int c = 0, d = 0;
    char *w = word;

    while(isspace(c = getchar()))
        ;
    if(c != EOF)
        *w++ = c;
    if(isalpha(c) || c == '_' || c == '#')
    {
        for(; --lim > 0; w++)
            if(!isalnum(*w = getchar()) && *w != '_')
            {
                ungetc(*w, stdin);
                break;
            }
        *w = '\0';
        return WORD;
    }
    if( c == '\'' || c == '"')
    {
        for(; --lim > 0; w++)
            if((*w = getchar()) == '\\')
                *++w = getchar();
            else if (*w == c)
            {
                ++w;
                break;
            }
            else if (*w == EOF)
                break;
        *w = '\0';
        return STRING;
    }
    if (c == '/')
    {
        if ((d = getchar()) == '/')
        {
            while(getchar() != '\n')
                ;
            ungetc('\n', stdin);
        }
        if (d == '*')
        {
            while((c = getchar()) != EOF)
                if(c == '*')
                {
                    if((c = getchar()) == '/')
                        break;
                    else
                        ungetc(c, stdin);
                }
        }
        else
            ungetc(d, stdin);
        *w = '\0';
        return COMMENT;
    }
    *w = '\0';
    return c;
}