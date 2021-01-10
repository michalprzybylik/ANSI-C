/*
Ćwiczenie 7.7. Zmień program wyszukujący według wzorca (z rozdz. 5) tak, aby 
przyjmował dane wejściowe z zestawu nazwanych polików lub ze standardowego 
wejścia, jeśli w argumentach wywołania nie podano żadnej nazwy pliku. Czy 
razem ze znalezionym wierszem trzeba wypisywać nazwę pliku, w którym go 
znaleziono.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLINE 1024

int findpatfile(char *pattern, char *fname, bool number, bool except);

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int c;
    long long int found = 0;
    bool except = false, number = false;
    FILE *ifp = NULL;
    char *program = argv[0];
    char *pattern;

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
                fprintf(stderr, "%s: nieznana opcja %c\n", program, c);
                exit(-1);
                break;
            }
    if (argc < 1)
    {
        fprintf(stderr, "Format wywołania: %s -x -n wzorzec [plik...]\n", program);
        exit(1);
    }
    pattern = *argv;
    if (argc == 1)
        found = findpatfile(pattern, "stdin", number, except);
    else
        while (--argc > 0)
            found += findpatfile(pattern, *++argv, number, except);
    printf("%s: znaleziono %lld wystapien %swzorca: %s\n", program, found, except ? "anty" : "", pattern);
    return 0;
}

int findpatfile(char *pattern, char *fname, bool number, bool except)
{
    char line[MAXLINE];
    long long int lineno = 0, found = 0;
    FILE *ifp;
    bool stdinput = strcmp("stdin", fname) == 0;

    if (stdinput)
        ifp = stdin;
    else if ((ifp = fopen(fname, "r")) == NULL)
    {
        fprintf(stderr, "findpatfile: nie moge otworzyc pliku %s\n", fname);
        exit(2);
    }
    while (fgets(line, MAXLINE, ifp) != NULL)
    {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except)
        {
            if (!stdinput)
                printf("plik %s:\n", fname);
            if (number)
                printf("%lld: ", lineno);
            printf("%s", line);
            found++;
        }
    }
    if(ferror(stdout))
    {
        fprintf(stderr, "findpatfile: blad pisania do stdout\n");
        exit(2);        
    }
    fclose(ifp);
    return found;
}