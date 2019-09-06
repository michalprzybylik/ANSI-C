#include<stdio.h>

float a();
int main()
{
    printf("%d",a(1.0));
    return 0;
}

float a(int b)
{
    return b++;
}
