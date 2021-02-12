#define NULL 0
#define EOF (-1)
#define BUFSIZE 4096
#define OPEN_MAX 20

typedef struct _iobuf
{
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;
extern FILE _iob[OPEN_MAX];

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
int fseek(FILE *fp, long offset, int orgin);


