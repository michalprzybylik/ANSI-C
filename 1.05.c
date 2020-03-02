/*
Ćwiczenie 1.5. Zmień program przekształcania temperatur tak, aby wypisywał zestawienie
w odwrotnej kolejności, to znaczy od 300 stopni do zera.
*/
#include <stdio.h>
#define LOWER 0
#define STEP 20
#define UPPER 300

int main()
{
    for (int fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    return 0;
}
