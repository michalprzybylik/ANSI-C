/* 
Ćwiczenie 8.7. Funkcja malloc akceptuje specyfikację rozmiaru bez sprawdzenia 
jej sensowności; funkcja free zakłada, że zwalniany blok zawiera poprawne pole 
rozmiaru. Zmień te funkcje tak, aby zadawały sobie więcej trudu przy wykrywaniu 
błędów. 
*/
#include <unistd.h>
#include <stdio.h>

#define NALLOC 1024
#define MAXALLOC 1024 * 1024 * 1024

typedef long long Align;

union header
{
    struct
    {
        union header *ptr;
        unsigned long size;
    } s;
    Align x;
};

typedef union header Header;

void *malloc(unsigned long nbytes);
Header *morecore(unsigned long nu);
void free(void *ap);
void *calloc(unsigned long n, unsigned long size);

Header base;
Header *freep = NULL;
unsigned long maxalloc;

int main (void)
{
    int *var;
    var = (int *)malloc(sizeof *var);
    *var = 2;
    printf("%d\n", *var);
    free(var);
    return 0;
}

void *malloc(unsigned long nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes == 0 || nbytes > MAXALLOC)
    {
        fputs("malloc: nieprawidlowa ilosc pamieci do przydzielenia\n", stderr);
        return NULL;
    }
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

Header *morecore(unsigned long nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = (char *)sbrk(nu * sizeof(Header));
    if (cp == (char *)-1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    maxalloc = maxalloc >= nu ? maxalloc : nu;
    free((void *)(up + 1));
    return freep;
}

void free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;
    if (bp->s.size == 0 || bp->s.size > maxalloc)
    {
        fputs("free: nieprawidlowy rozmiar zwalnianej pamieci", stderr);
        return;
    }
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr)
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp)
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    freep = p;
}

void *calloc(unsigned long n, unsigned long size)
{
    long long int nbytes;
    char *p, *pb;

    nbytes = n * size;;
    if ((pb = (char *)malloc(nbytes)) == NULL)
        return NULL;
    for (p = pb; p < pb + nbytes; p++)
        *p = 0;
    return (void *)pb;
}