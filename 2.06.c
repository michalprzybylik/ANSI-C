#include <stdio.h>

int setbits(int x, int p, int n, int y);

int main()
{
    printf("%d\n", setbits(0, 3, 3, 5));
    return 0;
}

int setbits(int x, int p, int n, int y)
{
    return (x & ~(~(~0 << n) << (p + 1 - n))) | (((y & ~(~0 << n))) << (p + 1 - n));
}