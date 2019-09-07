#include<stdio.h>

int rightrot(int x, int n);

int main()
{
    printf("%d\n", rightrot(1,3));
    return 0;
}

int rightrot(int x, int n)
{
    int wordlength;
    unsigned int w = ~0U;
    for(wordlength = 1; (w = w >> 1) > 0; ++wordlength)
        ;

    int i, lb;
    for(i = 0; i < n; ++i)
    {
        lb = (x & 1) << (wordlength - 1);
        x = x >> 1;
        x = x | lb;  
    } 
    return x;
}