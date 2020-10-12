/*
Zadanie 6.05. Napisz funkcję undef, która usuwa nazwę i jej definicję z tablicy 
obsługiwanej przez funkcję lookup i install.
*/
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 1001
#define HASHKEY 31

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

unsigned int hash(char *s);
struct nlist *lookup(char *s, struct nlist *hashtab[]);
struct nlist *install(char name[], char defn[], struct nlist *hashtab[]);
void undef(char *s, struct nlist *hashtab[]);
void undefall(struct nlist *hashtab[]);

unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + HASHKEY * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s, struct nlist *hashtab[])
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char name[], char defn[], struct nlist *hashtab[])
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name, hashtab)) == NULL)
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

void undef(char *s, struct nlist *hashtab[])
{
    unsigned int h = hash(s);
    struct nlist *np, *prev = NULL;

    for (np = hashtab[h]; np != NULL; np = np->next)
    {
        if (strcmp(s, np->name) == 0)
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

void undefall(struct nlist *hashtab[])
{
    struct nlist *ptr;

    for (int i = 0; i < HASHSIZE; i++)
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