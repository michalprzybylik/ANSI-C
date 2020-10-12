/*
Zadanie 6.06. Skonstuuj prostą wersję preprocesora obsługującego instrukcj 
#define (bezargumentowe), działającego na programach napisanych w języku 
C. Zastosuj funkcje opisane w tym rozdziale. Możesz też skorzystać z funkcji 
getch i ungetch.
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define DIR '#'
#define ERR 'E'
#define HASHVAL 31
#define HASHSIZE 1001

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

int gettoken(char token[], int lim);
int dir(struct nlist *hashtab[]);
void ungets(char str[]);
void skipblanks(void);
unsigned int hash(char *s);
struct nlist *lookup(char *s, struct nlist *hashtab[]);
struct nlist *install(char name[], char defn[], struct nlist *hashtab[]);
void undef(char defn[], struct nlist *hashtab[]);
void undefall(struct nlist *hashtab[]);

int main(void)
{
    char token[MAXWORD];
    static struct nlist *hashtab[HASHSIZE] = {NULL};
    struct nlist *p;

    while (gettoken(token, MAXWORD) != EOF)
    {
        if (token[0] == DIR)
        {
            if (dir(hashtab) == ERR)
                return 1;
        }
        else if (!isalpha(token[0]) && token[0] != '_')
            printf("%s", token);
        else if ((p = lookup(token, hashtab)) == NULL)
            printf("%s", token);
        else
            ungets(p->defn);
    }
    undefall(hashtab);
    return 0;
}

int gettoken(char token[], int lim)
{
    int c = 0, d = 0;
    char *w = token;

    while (isspace(c = getchar()))
        putchar(c);
    if (c != EOF)
        *w++ = c;
    if (isalpha(c) || c == '_')
    {
        for (; --lim > 0; w++)
            if (!isalnum(*w = getchar()) && *w != '_')
            {
                ungetc(*w, stdin);
                break;
            }
        *w = '\0';
        return token[0];
    }
    if (c == '\'' || c == '"')
    {
        for (; --lim > 0; w++)
            if ((*w = getchar()) == '\\')
                *++w = getchar();
            else if (*w == c)
            {
                ++w;
                break;
            }
            else if (*w == EOF)
                break;
    }
    if (c == '/')
    {
        if ((d = getchar()) == '/')
        {
            while (getchar() != '\n')
                ;
        }
        if (d == '*')
        {
            while ((c = getchar()) != EOF)
                if (c == '*')
                {
                    if ((c = getchar()) == '/')
                        break;
                    else
                        ungetc(c, stdin);
                }
        }
        else
            ungetc(d, stdin);
    }
    *w = '\0';
    return c;
}

int dir(struct nlist *hashtab[])
{
    int c, i;
    static char dir[MAXWORD], name[MAXWORD], defn[MAXWORD];

    if (!isalpha(gettoken(dir, MAXWORD)))
    {
        perror("dir: bledna dyrektywa preprocesora");
        return ERR;
    }
    if (strcmp(dir, "define") == 0)
    {
        skipblanks();
        if (!isalpha(gettoken(name, MAXWORD)) && name[0] != '_')
        {
            perror("dir: bledna nazwa w dyrektywie define");
            return ERR;
        }
        skipblanks();
        for (i = 0; i < MAXWORD - 1; i++)
            if ((defn[i] = getchar()) == EOF || defn[i] == '\n')
                break;
        defn[i] = '\0';
        if (i <= 0)
        {
            perror("dir: niekompletna dyrektywa define");
            return ERR;
        }
        install(name, defn, hashtab);
    }
    else if (strcmp(dir, "undef") == 0)
    {
        skipblanks();
        if (!isalpha(gettoken(name, MAXWORD)) && name[0] != '_')
        {
            perror("dir: bledna nazwa w dyrektywie undef");
            return ERR;
        }
        undef(name, hashtab);
    }
    else
    {
        perror("dir: bledna dyrektywa preprocesora");
        return ERR;
    }
    return 0;
}

void ungets(char *s)
{
    char *end = s + strlen(s);

    while (s < end)
        ungetc(*--end, stdin);
}

void skipblanks(void)
{
    int c;

    while (isblank((c = getchar())))
        ;
    ungetc(c, stdin);
}

unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + HASHVAL * hashval;
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