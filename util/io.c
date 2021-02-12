#include "io.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define PERM 0666

FILE _iob[OPEN_MAX] =
    {
        {0, (char *)0, (char *)0, _READ, 0},
        {0, (char *)0, (char *)0, _WRITE, 1},
        {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

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

int fseek(FILE *fp, long offset, int origin)
{
    int n;

    if (fp->flag & _READ)
    {
        if (origin == 1)
            offset -= fp->cnt;
        if (lseek(fp->fd, offset, origin) == -1)
            return EOF;
        fp->cnt = 0;
    }
    else if (fp->flag & _WRITE)
    {
        if (fflush(fp) == EOF)
            return EOF;
        lseek(fp->fd, offset, origin);
    }
    return 0;
}