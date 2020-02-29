/*
Ćwiczenie 1.3. Zmień program przekształcania temperatur tak, aby wypisywał również
nagłówek zestawienia.
*/
#include <stdio.h>

int main()
{
    float fahr, cels;
    int lower, step, upper;

    lower = 0;
    step = 20;
    upper = 300;
    fahr = lower;
    printf("Fahrenheit\tCelsius\n");
    while (fahr <= upper)
    {
        cels = (5.0 / 9.0) * (fahr - 32);
        printf("%10.0f\t%7.1f\n", fahr, cels);
        fahr = fahr + step;
    }
    return 0;
}