#include<stdio.h>

int bitcount (int x);

int main()
{
    printf("%d\n",bitcount(9));
    return 0;
}

int bitcount(int x)
{
    int i;
    for(i = 0; x > 0; x &= (x-1), ++i)
        ;
    return i;
}