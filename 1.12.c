#include<stdio.h>

int main()
{
    int c, isword = 0;
    while ( ( ( c = getchar() ) != EOF ) )
    {
        if( c == ' ' || c == '\t' || c =='\n' )
        {
            if (isword == 1)
            {
                putchar('\n');
                isword = 0;
            }
        }
        else
        {
            if( isword == 0 )
                isword = 1;
            putchar(c);
        }
    }
    return 0;
}