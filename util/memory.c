#include <unistd.h>
#include "memory.h"

static Header base;
static Header *freep = NULL;

static Header *morecore(unsigned long nu);

void *malloc(unsigned long nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits)
                prevp ->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
    }
    if (p == freep)
        if ((p = morecore(nunits)) == NULL)
            return NULL;
}

static Header *morecore(unsigned long nu)
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
    free((void *)(up + 1));
    return freep;
}

void free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;
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

unsigned long bfree(char *p, unsigned long nbytes)
{
    Header *hp;

    if (nbytes < sizeof(Header))
        return 0;
    hp = (Header *)p;
    hp->s.size = nbytes / sizeof(Header);
    free((void *)(hp + 1));
    return hp->s.size;
}