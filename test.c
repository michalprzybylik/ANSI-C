#include<stdio.h>

int main()
{
    printf("%d\n", a(-23));
    return 0;
}

int a(int a)
{
    return a % 10;
}