/*
Zadanie 5.17. Dodaj mechanizm obsługi pól tak, by można było przeprowadzić 
porządkowanie zawartości pól wewnątrz wierszy, stosując dla każdego pola niezależny 
zestaw opcji. (Skorowidz angielskiego oryginału tej książki był sortowany 
z użyciem opcji -df dla haseł i -n dla numerów stron.)
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINES 8192
#define MAXLEN 1024

char *lineptr[MAXLINES];
int numeric = 0;
int reverse = 0;
int character = 0;
int dict = 0;
int posbegin = 0;
int posend = MAXLEN;

int readparams(int argc, char *argv[]);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void sort(void *v[], int left, int right, int (*comp)(const void *s1, const void *s2));
int scmp(const char *s1, const char *s2);
int numcmp(const char *s1, const char *s2);
int charcmp(const char *s1, const char *s2);
int dictcmp(const char *s1, const char *s2);
int chardictcmp(const char *s1, const char *s2);

void tabfree(char *tab[], int size);

int main(int argc, char *argv[])
{
    int nlines;

    if (readparams(argc, argv))
    {
        int (*comp)(const void *s1, const void *s2);

        if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
        {
            if (numeric)
                comp = (int (*)(const void *, const void *))numcmp;
            else if (character && dict)
                comp = (int (*)(const void *, const void *))chardictcmp;
            else if (character)
                comp = (int (*)(const void *, const void *))charcmp;
            else if (dict)
                comp = (int (*)(const void *, const void *))dictcmp;
            else
                comp = (int (*)(const void *, const void *))scmp;
            sort((void **)lineptr, 0, nlines - 1, comp);
            writelines(lineptr, nlines);
        }
    }
    else
    {
        printf("Format wywołania: sort -n -r -f -d\n");
        return -1;
    }
    tabfree(lineptr, MAXLINES);
    return 0;
}

int readparams(int argc, char *argv[])
{
    int isvalnumber(char *s);
    int isvaloption(char *s);

    int c;

    while (--argc > 0 && ((*++argv)[0] == '-' || (*argv)[0] == '+'))
        if ((*argv)[0] == '-' && isvaloption(*argv + 1))
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
                case 'd':
                    dict = 1;
                    break;
                default:
                    printf("find: nieznana opcja %c\n", c);
                    argc = -1;
                    break;
                }
        else if ((*argv)[0] == '-' && isvalnumber(*argv + 1))
        {
            posbegin = atoi(*argv + 1);
            if (posbegin > MAXLEN - 1)
                posbegin = MAXLEN - 1;
        }
        else if ((*argv)[0] == '+' && isvalnumber(*argv + 1))
        {
            posend = atoi(*argv + 1);
            if (posend > MAXLEN)
                posend = MAXLEN;
        }
        else
            argc = -1;
    if (posbegin >= posend)
        argc = -1;
    if (argc == 0)
        return 1;
    else
        return 0;
}

int isvalnumber(char *s)
{
    while (isdigit(*s))
        s++;
    return !*s;
}

int isvaloption(char *s)
{
    while (isalpha(*s))
        s++;
    return !*s;
}

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
    if (reverse)
        for (int i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    else
        for (int i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
}

void sort(void *v[], int left, int right, int (*comp)(const void *s1, const void *s2))
{
    int i, last;
    static char str1[MAXLINES];
    static char str2[MAXLINES];
    void swap(void *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        strncpy(str1, v[i] + posbegin, posend - posbegin);
        strncpy(str2, v[left] + posbegin, posend - posbegin);
        if ((*comp)(str1, str2) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    sort(v, left, last - 1, comp);
    sort(v, last + 1, right, comp);
}

int scmp(const char *s1, const char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return *s1 - *s2;
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

int isdict(const char c);

int dictcmp(const char *s1, const char *s2)
{
    do
    {
        while (!isdict(*s1) && *s1 != '\0')
            s1++;
        while (!isdict(*s2) && *s2 != '\0')
            s2++;
    } while (*s1 != '\0' && *s1++ == *s2++);
    return *s1 - *s2;
}

int chardictcmp(const char *s1, const char *s2)
{
    do
    {
        while (!isdict(*s1) && *s1 != '\0')
            s1++;
        while (!isdict(*s2) && *s2 != '\0')
            s2++;
    } while (*s1 != '\0' && tolower(*s1++) == tolower(*s2++));
    return *s1 - *s2;
}

int isdict(const char c)
{
    return (isalnum(c) || c == ' ');
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