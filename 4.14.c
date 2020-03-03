/*
Ćwiczenie 4.14. Napisz definicję makra swap(t,x,y) zamienijącego miejscami wartości argumentów
x i y o typach t. (Skorzystaj ze struktury blokowej).
*/
#include <stdio.h>
#define swap(t, x, y) \
    {                 \
        t ___temp;    \
        ___temp = x;  \
        x = y;        \
        y = ___temp;  \
    }
    
int main(void)
{
    int a = 0, b = 1;
    printf("a = %d b = %d\n", a, b);
    swap(int, a, b);
    printf("a = %d b = %d\n", a, b);
    return 0;
}