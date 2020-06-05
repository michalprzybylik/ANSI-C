/*
Zadanie 5.15. Dodaj opcję -f powodującą utożsamianie małych i wielkich liter 
alfabetu tak, aby przynależność liter do różnych rejestrów nie miała wpływu na 
sposób sortowania; na przykład z porównania a i A ma wynikać równość.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 8192

char *lineptr[MAXLINES];
int numeric = 0;
int reverse = 0;
int character = 0;

int readparams(int argc, char *argv[]);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void sort(void *v[], int left, int right, int (*comp)(const void *s1, const void *s2));
int numcmp(const char *s1, const char *s2);
int charcmp(const char *s1, const char *s2);

void tabfree(char *tab[], int size);

int main(int argc, char *argv[])
{
    int nlines;

    if (readparams(argc, argv))
    {
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
        {
            if (numeric)
                sort((void **)lineptr, 0, nlines - 1, (int (*)(const void *, const void *))numcmp);
            else if (character)
                sort((void **)lineptr, 0, nlines - 1, (int (*)(const void *, const void *))charcmp);
            else
                sort((void **)lineptr, 0, nlines - 1, (int (*)(const void *, const void *))strcmp);
            writelines(lineptr, nlines);
        }
    }
    else
    {
        printf("Format wywołania: sort -n -r -f\n");
        return -1;
    }
    tabfree(lineptr, MAXLINES);
    return 0;
}

int readparams(int argc, char *argv[])
{
    int c;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c)
            {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            case 'f':
                character = 1;
                break;
            default:
                printf("find: nieznana opcja %c\n", c);
                argc = -1;
                break;
            }
    if (argc != 0)
        return 0;
    else
        return 1;
}

#define MAXLEN 1024

int readlines(char *lineptr[], int maxlines)
{
    int getl(char *s, int lim);
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = getl(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = (char *)malloc(len)) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

int getl(char *s, int lim)
{
    int c;
    char *p = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - p;
}

void writelines(char *lineptr[], int nlines)
{
    if (!reverse)
        for (int i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
    else
        for (int i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
}

void sort(void *v[], int left, int right, int (*comp)(const void *s1, const void *s2))
{
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    sort(v, left, last - 1, comp);
    sort(v, last + 1, right, comp);
}

int numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int charcmp(const char *s1, const char *s2)
{
    for (; tolower(*s1) == tolower(*s2); s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return *s1 - *s2;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void tabfree(char *tab[], int size)
{
    for (int i; i < size; i++)
        free(tab[i]);
}