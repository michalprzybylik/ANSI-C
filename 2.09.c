/*
Ćwiczenie 2.9. W arytmetyce uzupełnieniowej do 2 wyrażenie x&=(x-1) usuwa 
jedynkę ze skrajnie prawego bitu zmiennej x. Wyjaśnij, dlaczego. Zastosuj tę 
obserwację do napisania szybszej wersji funkcja bitcount.
*/
#include <stdio.h>

int bitcount(int x);

int main()
{
    printf("%d\n", bitcount(9));
    return 0;
}

int bitcount(int x)
{
    int i;
    for (i = 0; x > 0; x &= (x - 1), ++i)
        ;
    return i;
}
