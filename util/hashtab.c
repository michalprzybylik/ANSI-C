#include <stdlib.h>
#include <string.h>
#include "hashtab.h"

static struct nlist *hashtab[] = {NULL};

unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + HASHKEY * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL)
    {
        np = (struct nlist *)malloc(sizeof(struct nlist));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free(np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name)
{
    unsigned int h = hash(name);
    struct nlist *np, *prev = NULL;

    for (np = hashtab[h]; np != NULL; np = np->next)
    {
        if (strcmp(name, np->name) == 0)
            break;
        prev = np;
    }
    if (np != NULL)
    {
        if (prev == NULL)
            hashtab[h] = np->next;
        else
            prev->next = np->next;
        free(np->name);
        free(np->defn);
        free(np);
    }
}

void undefall(void)
{
    struct nlist *ptr;

    for(int i = 0; i < HASHSIZE; i++)
    {
        while (hashtab[i] != NULL)
        {
            ptr = hashtab[i]->next;
            free(hashtab[i]->name);
            free(hashtab[i]->defn);
            free(hashtab[i]);
            hashtab[i] = ptr;
        }
    }
}