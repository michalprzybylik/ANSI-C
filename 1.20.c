#include <stdio.h>

#define TABSIZE 8

int main(void)
{
    int c, pos, toadd;
    while ((c = getchar()) != EOF)
    {
        if (pos > TABSIZE - 1)
            pos = 0;
        if (c == '\t')
        {
            toadd = TABSIZE - pos;
            while (toadd > 0)
            {
                putchar(' ');
                --toadd;
            }
            pos = 0;
        }
        else if (c == '\n')
        {
            putchar(c);
            pos = 0;
        }
        else
        {
            putchar(c);
            ++pos;
        }
    }
    return 0;
}