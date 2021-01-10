/*
Ćwiczenie 7.8. Utwórz program wypisujący zawartość zestawu plików, z których 
każdy rozpoczyna się na nowej stronie. Wszystkie strony powinny być opatrzone 
tytułem i bieżącym numerem strony w ramach każdego pliku z osobna.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 128
#define PAGELEN 32

void filepagecopy(FILE *ifp, char *ifname);

int main(int argc, char *argv[])
{
    FILE *fp;
    char *prog = argv[0];

    if (argc == 1)
        filepagecopy(stdin, "");
    else
        while (--argc > 0)
            if((fp = fopen(*++argv, "r")) == NULL) 
            {
                fprintf(stderr, "%s: nie moge otworzyc %s\n", prog, *argv);
                exit(1);
            }
            else
            {
                filepagecopy(fp, *argv);
                fclose(fp);
            }
    if (ferror(stdout))
    {
        fprintf(stderr, "%s: blad pisania do stdout\n", prog);
        exit(2);        
    }
    return 0;
}

void filepagecopy(FILE *ifp, char *ifname)
{
    char line[MAXLINE];
    long long int lineno = 0, pageno = 1;

    while(fgets(line, MAXLINE, ifp) != NULL)
    {
        if (lineno == PAGELEN)
        {
            pageno++;
            lineno = 0;
        }
        if (lineno == 0)
            printf("==> plik: %s, strona %lld <==\n", ifname, pageno);
        lineno++;
        fputs(line, stdout);
    }
    fclose(ifp);
}