/*
Ćwiczenie 7.6. Napisz program porwnujący dwa pliki i wypisujący dwa pliki i wypisujący pierwszy 
wiersz, w którym te pliki się różnią.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 128

void usage(char *pname);
void fopenerr(char *pname, char *fname);

int main(int argc, char *argv[])
{
    FILE *fap, *fbp;
    char linea[MAXLINE], lineb[MAXLINE];
    char *lpa, *lpb;
    int nline = 0;

    if (argc != 3)
        usage(argv[0]);
    if ((fap = fopen(argv[1], "r")) == NULL)
        fopenerr(argv[0], argv[1]);
    if ((fbp = fopen(argv[2], "r")) == NULL)
        fopenerr(argv[0], argv[2]);
    while ((lpa = fgets(linea, MAXLINE, fap)) != NULL && (lpb = fgets(lineb, MAXLINE, fbp)) != NULL)
    {
        nline++;
        if (strcmp(linea, lineb) != 0)
        {
            printf("pierwsza roznica w wierszu %d:\npierwszy plik %s:\n%s\ndrugi plik %s:\n%s\n", nline, argv[1], linea, argv[2], lineb);
            return 0;
        }
    }
    nline++;
    if (lpa == NULL)
    {
        printf("koniec pierwszego pliku w wierszu %d:\ndrugi plik: %s:\n%s", nline, argv[2] ,lineb);
        return 0;  
    }
    if (lpb == NULL)
    {
        printf("koniec drugiego pliku w wierszu %d:\npierwszy plik %s:\n%s", nline, argv[1], linea);
        return 0;  
    }

    puts("pliki sa takie same");
    return 0;
}

void usage(char *pname)
{
    fprintf(stderr, "Użycie %s: %s filea fileb\n", pname, pname);
    exit(1);
}
void fopenerr(char *pname , char *fname)
{
    fprintf(stderr, "%s: nie moge otworzyc pliku %s\n", pname, fname);
    exit(2);
}