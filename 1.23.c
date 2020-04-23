/*
Ćwiczenie 1.23. Napisz program usuwający wszystkie komentarze z dowolnego 
programu w języku C. Nie zapomnij o właściwym traktowaniu stałych znakowych 
i napisowych. Komentarze języka C nie mogą być zagnieżdżone. 
*/
#include <stdio.h>

int main()
{
    int c, d, tmp, esc;
    int inqma, inqmb;
    inqma = inqmb = 0;
    esc = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\\')
            if (esc == 0)
                esc = 1;
            else
                esc = 0;
        else if (esc == 0)
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
        }
        else
            esc = 0;
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
                    if (d == '*')
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