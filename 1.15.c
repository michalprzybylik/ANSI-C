/*
Ćwiczenie 1.15. Napisz nową wersję programu przekształcania temperatur
z p. 1.2, w której przekształceń tych dokonuje funkcja.
*/
#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

double fahr_to_cels(int);

int main()
{
    for (int fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, fahr_to_cels(fahr));
    return 0;
}

double fahr_to_cels(int fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}