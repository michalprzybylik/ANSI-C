#include <stdio.h>

int invert(int x, int p, int n);

int main()
{
    printf("%d\n", invert(0, 2, 3));
    return 0;
}

int invert(int x, int p, int n)
{
    return x ^ ((~(~0 << n)) << (p + 1 - n));
}