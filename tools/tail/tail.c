/*
Zadanie 5.13. Napisz program tail wypisujący n ostatnich wierszy tekstu podanego 
na wejściu. Niech n będzie domyślnie równe 10, ale tę wartość można 
zmienić za pomocą opcjonalnego argumentu wywołania programu. Zatem zlecenie 

tail -n

spowoduje wypisanie n ostatnich wierszy. Program powienien działać sensownie 
niezależnie od tego, jak nierozsądne są dane wejściowe lub wartość n. Napisz 
ten program tak, aby jak najlepiej wykorzystywał dostępną mu pamięć: wiersze powinny
być gromadzone podobnie jak w programie sortującym z p. 5.6, nie zaś 
w dwuwymiarowej tablicy o stałym rozmiarze.
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define ERRPARAMS 1
#define ERRLINES 2
#define MAXLINES 8192 
#define LINESTOPRINT 10

char **lineptr;
int number = 0;
int nlinestoprint = LINESTOPRINT;

int readparams(int argc, char *argv[]);
char **readlines(char **lineptr, int maxlines, long int *nlines);
void writelines(char **lineptr, char **ptr, long int nlines);

int main(int argc, char *argv[])
{
    char **ptr; 
    long int nlines;
    if (readparams(argc, argv))
    {
        lineptr = (char **)malloc(sizeof(char *) * nlinestoprint);
        for (int i = 0; i < nlinestoprint; i++)
            lineptr[i] = NULL;
        if ((ptr = readlines(lineptr, MAXLINES, &nlines)) != NULL)
            writelines(lineptr, ptr, nlines);
        else
        {
            printf("blad: za duzo wierszy do przetworzenia\n");
            return ERRLINES;
        }
    }
    else
        return ERRPARAMS;
    ptr = lineptr;
    for (int i = 0; i < nlinestoprint; i++)
        free(*ptr++);
    free(lineptr);
    return 0;
}

int readparams(int argc, char *argv[])
{
    int c;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
        {
            if (isdigit(c))
                c = -1;
            switch (c)
            {
            case -1:
                nlinestoprint = atoi(*argv);
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("tail: nieznana opcja %c\n", c);
                argc = 0;
                break;
            }
            if (c == -1)
                break;
        }
    if (argc != 0)
    {
        printf("format wywolania: tail [-liczba wierszy] [-n]\n");
        return 0;
    }
    if (nlinestoprint <= 0 || nlinestoprint > MAXLINES)
        nlinestoprint = MAXLINES;
    return 1;
}

#include "../../util/getl.h"
#define MAXLEN 1024

char **readlines(char **lineptr, int maxlines, long int *nlines)
{
    int len, nline = 0;
    char **ptr = lineptr, line[MAXLEN];
    while ((len = getl(line, MAXLEN)) > 0)
    {
        if (ptr - lineptr >= nlinestoprint)
            ptr = lineptr;
        free(*ptr);
        if ((nlinestoprint == maxlines && nline > maxlines) || (*ptr = malloc(len)) == NULL)
            return NULL;
        else
        {
            line[len - 1] = '\0';
            strcpy(*ptr++, line);
            nline++;
        }
    }
    *nlines = nline;
    return ptr;
}

void writelines(char **lineptr, char **ptr, long int nlines)
{
    long int n = (nlinestoprint > nlines) ? nlines : nlinestoprint;
    for (long int i = 1; i <= n; i++)
    {
        if (ptr - lineptr >= n)
            ptr = lineptr;
        if (number)
            printf("%ld: ", nlines - n + i);
        printf("%s\n", *ptr++);
    }
}