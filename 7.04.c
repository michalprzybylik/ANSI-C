/*
Zadanie 7.03. Napisz prywatną wersję funkcji scanf, analogiczną do minprintf 
z poprzedniego punktu.
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFLEN 32
#define MAXFMT 32

int minscanf(char *fmt, ...);

int main(void)
{
    int i;
    float f;
    char s[BUFLEN]; 
    minscanf("%s%f%i", &s, &f, &i);
    printf("%f %s %i\n", f, s, i);
}

int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, locfmt[MAXFMT];
    int *ival, i;
    unsigned int *uval;
    float *dval;
    int argc = 0;

    va_start(ap, fmt);
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }

        i = 0;
        locfmt[i++] = '%';
        p++;
        if (*p == '-')
        {
            locfmt[i++] = '-';
            p++;
        }
        for (; i < MAXFMT - 2 && isnumber(*p); p++, i++)
        {
            locfmt[i] = *p;
        }
        if (i < MAXFMT - 2 && *p == '.')
        {
            locfmt[i++] = '.';
            p++;
        }
        for (; i < MAXFMT - 2 && isnumber(*p); p++, i++)
        {
            locfmt[i] = *p;
        }
        locfmt[i++] = *p;
        locfmt[i] = '\0';

        switch (*p)
        {
        case 'd':
        case 'i':
            ival = va_arg(ap, int *);
            argc += scanf(locfmt, ival);
            break;
        case 'c':
        case 'u':
            uval = va_arg(ap, unsigned int *);
            argc += scanf(locfmt, uval);
            break;
        case 'f':
            dval = va_arg(ap, float *);
            argc += scanf(locfmt, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            argc += scanf(locfmt, sval);
            break;
        default:
            break;
        }
        i = 0;
    }
    va_end(ap);
    return argc;
}
