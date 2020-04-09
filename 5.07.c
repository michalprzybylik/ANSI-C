/*
Ćwiczenie 5.7. Zmień funkcję readlines tak, aby budowała wiersze w tablicy dostarczonej
przez funkcję main, a nie w obszarach pamięci przydzielanych przez
funkcję alloc. O ile szybszy jest program?
*/
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXSTORE 10000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char linestore[], int maxlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main(void)
{

    int nlines;
    char linestore[MAXSTORE];

    if ((nlines = readlines(lineptr, linestore, MAXLINES)) >= 0)
    {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("blad: za duzo wierszy do sortowania\n");
        return 1;
    }
}

#define MAXLEN 1000
#include "util/getl.h"

int readlines(char *lineptr[], char linestore[], int maxlines)
{
    int len, nlines = 0;
    char *p = linestore, line[MAXLEN];

    while ((len = getl(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p + len > linestore + MAXSTORE)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void qsort(char *lineptr[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)
        return;
    swap(lineptr, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(lineptr[i], lineptr[left]) < 0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    qsort(lineptr, left, last - 1);
    qsort(lineptr, last + 1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
