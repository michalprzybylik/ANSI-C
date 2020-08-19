#include <string.h>

int binsearch(int a, int tab[], int n)
{
    int low = 0, high = n - 1, mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(tab[mid] < a)
            high = mid - 1;
        else if (tab[mid] > a)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int strbinsearch(char *s, char *tab[], int n)
{
    int low = 0, high = n - 1, mid;
    int cmp = 0;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if((cmp = strcmp(s, tab[mid])) < 0)
            high = mid - 1;
        else if (cmp > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}