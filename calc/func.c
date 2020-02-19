#include <stdio.h>
#include <math.h>
#include <string.h>
#include "calc.h"

void fun(char s[])
{
    double op;
    if(!strcmp(s, "sin"))
        push(sin(pop()));
    else if (!strcmp(s, "cos"))
        push(cos(pop()));
    else if (!strcmp(s, "tan"))
        push(tan(pop()));
    else if (!strcmp(s, "ln"))
        push(log(pop()));
    else if (!strcmp(s, "log"))
        push(log10(pop()));
    else if (!strcmp(s, "log"))
        push(log10(pop()));
    else if (!strcmp(s, "pow"))
    {
        op = pop();
        push(pow(pop(),op));
    }
    else if (!strcmp(s, "sqrt"))
        push(sqrt(pop()));
    else if (!strcmp(s, "ceil"))
        push(ceil(pop()));
    else if (!strcmp(s, "floor"))
        push(floor(pop()));
    else if (!strcmp(s, "abs"))
        push(fabs(pop()));
    else if (!strcmp(s, "inv"))
        push(inv(pop()));
    else
        printf("Blad: brak implementacji funkcji %s\n", s);
}

double inv(double f)
{
    return -f;
}