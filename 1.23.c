#include <stdio.h>

int main()
{
    int c, d;
    int inqma, inqmb;
    inqma = inqmb = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\'')
            if (inqma == 0)
                inqma = 1;
            else
                inqma = 0;

        if (c == '"')
            if (inqmb == 0)
                inqmb = 1;
            else
                inqmb = 0;

        if (c == '/' && inqma == 0 && inqmb == 0)
        {
            d = getchar();
            if (d == '/')
                while ((d = getchar()) != '\n')
                    ;
            else if (d == '*')
                while ((d = getchar()) != '*')
                    if(getchar() == '/')
                        break;
        }
        else
            putchar(c);
    }
    return 0;
}