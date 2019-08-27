#include<stdio.h>

int main()
{
    float cels, fahr;
    float lower, step, upper;

    lower = -30;
    step = 10;
    upper = 100;
    cels = lower;
    printf("Celsius\tFahrenheit\n");
    while(cels <= upper)
    {
        fahr = (9.0/5.0) * cels + 32;
        printf("%7.0f\t%10.1f\n", cels, fahr);
        cels = cels + step;
    }
    return 0;
}