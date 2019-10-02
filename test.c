#include<stdio.h>

ab(float a);

int main()
{
    float a = 0;
    printf("%f",ab(a));
    return 0;
}

int ab(float a)
{
    return (int)++a;
}
