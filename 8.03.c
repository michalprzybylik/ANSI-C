/* 
Ćwiczenie 8.3. Zaprojektuj i napisz funkcje _flushbuf, fflush i flose.
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#undef NULL
#define NULL 0
#define EOF (-1)
#define BUFSIZE 4096
#define OPEN_MAX 20
#define PERM 0666

typedef struct _iobuf
{
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;

#define stdin (_iob)
#define stdout (_iob + 1)
#define stderr (_iob + 2)

enum _flags
{
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(c, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (c) : _flushbuf((c), p))

#define getchar() getc(stdin)
#define putchar(c) putc((c), stdout)

FILE *fopen(char *name, char *mode);
int _fillbuf(FILE *fp);
int _flushbuf(int c, FILE *fp);
int fflush(FILE *fp);
int fclose(FILE *fp);

FILE _iob[OPEN_MAX] =
    {
        {0, (char *)0, (char *)0, _READ, 0},
        {0, (char *)0, (char *)0, _WRITE, 1},
        {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

int main(void)
{
    char c;
    FILE *fp = fopen("file.txt", "w");
    for (int i = 0; i < 1024; i++)
        putc(i % 128, fp);
    fclose(fp);
    fp = fopen("file.txt", "r");
    while ((c = getc(fp)) != EOF)
        putchar(c);
    fflush(stdout);
    return 0;
}

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    fp->fd = fd;
    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->base, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

int _flushbuf(int x, FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
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
            fp->flag |= _ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    *fp->ptr++ = (char)x;
    fp->cnt = bufsize - 1;
    return x;
}

int fflush(FILE *fp)
{
    if (_flushbuf(0, fp))
        return EOF;
    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
    return 0;
}

int fclose(FILE *fp)
{
    int sc = 0;

    if (fp->flag & _WRITE)
        sc = fflush(fp);
    free(fp->base);
    fp->base = NULL;
    fp->flag = 0;
    return sc;
}