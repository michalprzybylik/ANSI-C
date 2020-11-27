/*
Zadanie 7.03. Uzupełnij minprintf tak, aby obsługiwała więcej możliwości funkcji 
printf. 
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXFMT 32

void minprintf(char *fmt, ...);

int main(void)
{
    minprintf("%o\n", 25);
}

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, locfmt[MAXFMT];
    int ival, i;
    unsigned int uval;
    double dval;
    void *pval;

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
            ival = va_arg(ap, int);
            printf(locfmt, ival);
            break;
        case 'c':
        case 'u':
        case 'o':
        case 'x':
        case 'X':
            uval = va_arg(ap, unsigned int);
            printf(locfmt, uval);
            break;
        case 'f':
        case 'F':
        case 'e':
        case 'E':
            dval = va_arg(ap, double);
            printf(locfmt, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            printf(locfmt, sval);
            break;
        case 'p':
            pval = va_arg(ap, void *);
            printf(locfmt, pval);
            break;
        default:
            putchar(*p);
            break;
        }
        va_end(ap);
    }
}
