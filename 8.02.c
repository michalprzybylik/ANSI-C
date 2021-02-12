/* 
Ćwiczenie 8.2. Napisz nowe wersje funkcji fopen i _fillbuf, uywając pól zamiast 
jawnych operacji bitowych. Porównaj rozmiar kodu i prędkość działania obu wersji.
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#undef NULL
#define NULL 0
#define EOF (-1)
#define BUFSIZE 4
#define OPEN_MAX 20

typedef struct _iobuf
{
    int cnt;
    char *ptr;
    char *base;
    struct
    {
        unsigned int _READ : 1;
        unsigned int _WRITE : 1;
        unsigned int _UNBUF : 1;
        unsigned int _EOF : 1;
        unsigned int _ERR : 1;
    } flag;
    int fd;
} FILE;

#define stdin (_iob)
#define stdout (_iob + 1)
#define stderr (_iob + 2)

#define feof(p) (((p)->flag._EOF) != 0)
#define ferror(p) (((p)->flag._ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(c, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (c) : _flushbuf((c), p))

#define getchar() getc(stdin)
#define putchar(c) putc((c), stdout)

#define PERM 0666

FILE _iob[OPEN_MAX] =
    {
        {0, (char *)0, (char *)0, {1, 0, 0, 0, 0}, 0},
        {0, (char *)0, (char *)0, {0, 1, 0, 0, 0}, 1},
        {0, (char *)0, (char *)0, {0, 1, 1, 0, 0}, 2}
    };

FILE *fopen(char *name, char *mode);
int _fillbuf(FILE *fp);
int _flushbuf(int c, FILE *fp);

int main(void)
{   
    char c;

    while((c = getchar()))
        putchar(c);
    
    return 0;
}

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flag._READ == 0 && fp->flag._WRITE == 0)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERM);
    else if (*mode == 'a')
    {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERM);
        lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->cnt = 0;
    fp->ptr = fp->base = NULL;
    if (*mode == 'r')
        fp->flag._READ = 1;
    else
        fp->flag._WRITE = 1;
    fp->fd = fd;
    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;

    if (fp->flag._READ == 0 || fp->flag._EOF == 1 || fp->flag._ERR == 1)
        return EOF;
    bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZE;
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->base, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
    int bufsize;

    if (fp->flag._WRITE == 0 || fp->flag._ERR == 1)
        return EOF;
    bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZE;
    if (fp->base == NULL)
    {
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    }
    else
    {
        int n = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, n) != n)
        {
            fp->flag._ERR = 1;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    *fp->ptr++ = (char)c;
    fp->cnt = bufsize - 1;
    return c;
}