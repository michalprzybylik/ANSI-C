#include <stdio.h>

int main()
{
    int c, d, tmp;
    int inqma, inqmb;
    inqma = inqmb = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\'')
        {
            if (inqma == 0)
                inqma = 1;
            else
                inqma = 0;
        }
        if (c == '"')
        {
            if (inqmb == 0)
                inqmb = 1;
            else
                inqmb = 0;
        }
        if (c == '/' && inqma == 0 && inqmb == 0)
        {
            d = getchar();
            if (d == '/')
            {
                while ((getchar()) != '\n')
                    ;
                putchar('\n');
            }
            else if (d == '*')
                {
                    c = 0;
                while ((d = getchar()) != '/' || c != 1)
                    {
                    c = 0;
                    if(d == '*')
                        c = 1;
                    }
                }
            else
            {
                putchar(c);
                putchar(d);
            }
        }
        else
            putchar(c);
    }
    return 0;
}