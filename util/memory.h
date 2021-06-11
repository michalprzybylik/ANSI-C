#define NALLOC 1024

typedef unsigned long long Align;

union header 
{
    struct
    {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

void *malloc(unsigned long nbytes);
void *calloc(unsigned long n, unsigned long size);
void free(void *ap);
unsigned long bfree(char *p, unsigned long nbytes);