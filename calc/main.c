#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"

#define MAXOP 100
#define VARNR 26

int main(void)
{
    int type, var;
    double op2, lastval = 0.0;
    char s[MAXOP];
    double vars[VARNR];
    for (int i = 0; i < VARNR; ++i)
        vars[i] = 0.0;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("Blad: dzielenie przez 0\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("Blad: dzielenie przez 0\n");
            break;
        case '\n':
            printf("\t%.8g\n", lastval = pop());
            break;
        case '?':
            printf("\t%.8g\n", top());
            break;
        case 'C':
            clear();
            break;
        case 'S':
            swap();
            break;
        case 'D':
            dstack();
            break;
        case FUN:
            fun(s);
            break;
        case '=':
            pop();
            if(islower(var))
                vars[var - 'a'] = top();
            else
                printf("Blad: brak nazwy zmiennej\n");
            break;
        default:
            if(islower(type))
                push(vars[type - 'a']);
            else if (type == 'V')
                push(lastval);
            else
                printf("Blad: nieznane polecenie %s\n", s);
            break;
        }
        var = type;
    }
    return 0;
}