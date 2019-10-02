#include<stdio.h>
#define len 4
#define s 1

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main(void)
{
    int v[len]={0,1,3,4};
    printf("index: %d\n", binsearch(s, v, len));
    printf("index: %d\n", binsearch2(s, v, len));
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low = 0, high = n - 1, mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binsearch2(int x, int v[], int n)
{
    int low = 0, high = n - 1, mid;
    while(low != high)
    {
        mid = (low + high) / 2;
        if (x > v[mid])
            low = mid + 1;
        else
            high = mid;
    }
    if(x == v[high])
        return high;
    return -1;
}