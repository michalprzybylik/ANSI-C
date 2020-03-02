/*
Ćwiczenie 4.13. Napisz rekurencyjną wersję funkcji reverse(s), która odwraca 
kolejność znaków tekstu w s.
*/
#include <stdio.h>
#include <string.h>

char s[] = "0123456789";
void reverse(char s[]);

int main(void)
{
    int len = strlen(s) - 1;
    reverse(s);
    printf("%s\n", s);
    return 0;
}

void reverse(char s[])
{
    void reverser(char s[], int left, int right);
    reverser(s, 0, strlen(s) - 1);
}

void reverser(char s[], int left, int right)
{
    void swap(char s[], int i, int j);
    if (left >= right)
        return;
    swap(s, left, right);
    reverser(s, left + 1, right - 1);
}

void swap(char s[], int i, int j)
{
    char tmp;
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}