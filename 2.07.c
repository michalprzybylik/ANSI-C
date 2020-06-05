/*
Ćwiczenie 2.7. Napisz funkcję inwert(x,p,n) zwracającą wartość x, w której n bitów 
- poczynając od pozycji p - zamieniono z 1 na 0 i odwrotnie. Pozostałe bity 
x nie powinny ulec zmianie.
*/
#include <stdio.h>

int inwert(int x, int p, int n);

int main()
{
    printf("%d\n", inwert(0, 2, 3));
    return 0;
}

int inwert(int x, int p, int n)
{
    return x ^ ((~(~0 << n)) << (p + 1 - n));
}