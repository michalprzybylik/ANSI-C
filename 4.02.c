/*
Ćwiczenie 4.2. Uzupełnij funkcję atof tak, aby obsługiwała także "naukową" (wykładniczą) 
notację o postaci

123.45e-6

w której bezpośrednio po liczbie zmiennoprzecinkowej może wystąpić litera e lub 
E oraz wykładnik ewentualnie ze znakiem liczby.
*/
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int main(void)
{
    int mygetline(char line[], int lim);
    double sum = 0, atof(char s[]);
    char line[MAXLINE];
    while (mygetline(line, MAXLINE))
        printf("\t%g\n", sum += atof(line));
    return 0;
}

double atof(char s[])
{
    double val, power;
    int i, sign, expval = 0;
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    val = sign * val / power;
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (expval = 0; isdigit(s[i]); i++)
            expval = 10 * expval + (s[i] - '0');
        if (sign == 1)
            while (expval--)
                val *= 10.0;
        else
            while (expval--)
                val /= 10.0;
    }
    return val;
}

int mygetline(char line[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return i;
}