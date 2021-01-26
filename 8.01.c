/* 
Ćwiczenie 8.1. Zmień program cat z rozdz. 7 używając funkcji read, write, open 
i close zamiast ich odpowiedników z biblioteki standardowej. Przeprowadź eksperymenty 
porównując względne szybkości obu wersji.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>

#define BUFSIZE 4096 

bool filecopy(int ifd, int ofd);
void error(char *fmt, ...);

int main(int argc, char *argv[])
{
    int fd;

    if (argc == 1)
        filecopy(0, 1);
    else
        while (--argc > 0)
            if((fd = open(*++argv, O_RDONLY)) == -1) 
                error("cat: nie moge otworzyc %s", *argv);
            else
            {
                if(!filecopy(fd, 1))
                    error("cat: blad pisania do pliku %s", *argv);
                close(fd);
            }
    return 0;
}

bool filecopy(int ifd, int ofd)
{
    int n = 0;
    static char buf[BUFSIZE];

    while((n = read(ifd, buf, BUFSIZE)))
        if (write(ofd, buf, n) != n)
            return false;
    return true;
}

void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    write(2, "error: ", 7);
    vfprintf(stderr, fmt, args);
    write(2, "\n", 1);
    va_end(args);
    exit(1);
}
