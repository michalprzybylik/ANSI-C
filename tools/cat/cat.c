#include <stdio.h>
#include <stdlib.h>

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[])
{
    FILE *fp;
    char *prog = argv[0];

    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if((fp = fopen(*++argv, "r")) == NULL) 
            {
                fprintf(stderr, "%s: nie moge otworzyc %s\n", prog, *argv);
                exit(1);
            }
            else
            {
                filecopy(fp, stdout);
                fclose(fp);
            }
    if (ferror(stdout))
    {
        fprintf(stderr, "%s: blad pisania do stdout\n", prog);
        exit(2);        
    }
    return 0;
}

void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while((c = getc(ifp)) != EOF)
        putc(c, ofp);
}