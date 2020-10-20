/*
Zadanie 7.01. Napisz program, który przekształca wielkie litery na małe lub małe 
litery na wielkie w zależności ot tego, z jaką nazwą został wywołany; nazwa ta 
figuruje w argv[0].
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <libgen.h>

struct
{
    unsigned int lower : 1;
    unsigned int upper : 1;
} flags;

int main(int argc, char *argv[])
{
    char *name = basename(argv[0]);
    int c;

    if (strcmp(name, "lower") == 0)
        flags.lower = 1;
    else if (strcmp(name, "upper") == 0)
        flags.upper = 1;

    while ((c = getchar()) != EOF)
    {
        if (flags.lower == 1)
            c = tolower(c);
        else if (flags.upper == 1)
            c = toupper(c);
        putchar(c);
    }
    return 0;
}