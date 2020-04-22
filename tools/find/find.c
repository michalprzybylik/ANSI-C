#include <stdio.h>
#include <string.h>

#define MAXLINE 1024
#include "../../util/getl.h"

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long int lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: nieznana opcja %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
    if (argc != 1)
        printf("Format wywołania: find -x -n wzorzec\n");
    else
        while (getl(line, MAXLINE) > 0)
        {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except)
            {
                if (number)
                    printf("%ld: ", lineno);
                printf("%s", line);
                found++;
            }
        }
    return found;
}
