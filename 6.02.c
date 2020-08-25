/*
Zadanie 6.02. Napisz program, który czyta tekst programu napisanego w C i wypisuje 
w porządku alfabetycznym wszystkie grupy nazw zmiennych o identycznych 
sześciu początkowych znakach i różniących się którymkolwiek z dalszych 
znaków. Nie zliczaj słów występujących w stałych napisowych i w komentarzach. 
Niech liczba 6 będzie parametrem, który można zmienić w wierszu wywołania 
programu.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 128
#define COMPLEN 6
#define KEYSIZE (sizeof keytab / sizeof keytab[0])

enum tokentypes
{
    WORD,
    COMMENT,
    STRING
};

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

char *keytab[] =
    {
        "auto",
        "break",
        "case",
        "char",
        "const",
        "continue",
        "default",
        "do",
        "double",
        "else",
        "enum",
        "extern",
        "float",
        "for",
        "goto",
        "if",
        "int",
        "long",
        "register",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "struct",
        "switch",
        "typedef",
        "union",
        "unsigned",
        "void",
        "volatile",
        "while"
    };

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
void printn(char *s, int n);
int getword(char*, int);
void treefree(struct tnode *);
int readparams(int argc, char *argv[]);
int binsearch(char *s, char *tab[], int n);
int complen = COMPLEN;

int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD] = "";
    char type = '\0';
    if(readparams(argc, argv))
    {
        while((type = getword(word, MAXWORD)) != EOF)
            if(type == WORD && binsearch(word, keytab, KEYSIZE) == -1)
                root = addtree(root, word);
        treeprint(root);
        printf("\n");
        treefree(root);
        return 0;
    }
    else
        return 1;
}

int getword(char *word, int lim)
{
    int c = 0, d = 0;
    char *w = word;

    while(isspace(c = getchar()))
        ;
    if(c != EOF)
        *w++ = c;
    if(isalpha(c) || c == '_')
    {
        for(; --lim > 0; w++)
            if(!isalnum(*w = getchar()) && *w != '_')
            {
                ungetc(*w, stdin);
                break;
            }
        *w = '\0';
        return WORD;
    }
    if( c == '#')
    {
        while(!isblank(getchar()))
            ;
    }
    if( c == '\'' || c == '"')
    {
        for(; --lim > 0; w++)
            if((*w = getchar()) == '\\')
                *++w = getchar();
            else if (*w == c)
            {
                ++w;
                break;
            }
            else if (*w == EOF)
                break;
        return STRING;
    }
    if (c == '/')
    {
        if ((d = getchar()) == '/')
        {
            while(getchar() != '\n')
                ;
        }
        if (d == '*')
        {
            while((c = getchar()) != EOF)
                if(c == '*')
                {
                    if((c = getchar()) == '/')
                        break;
                    else
                        ungetc(c, stdin);
                }
        }
        else
            ungetc(d, stdin);
        return COMMENT;
    }
    *w = '\0';
    return c;
}

struct tnode *addtree(struct tnode *ptr, char *str)
{
    int comp = 0;
    if (ptr == NULL)
    {
        ptr = (struct tnode *)malloc(sizeof(struct tnode));
        ptr->word = strdup(str);
        ptr->count = 1;
        ptr->left = ptr->right = NULL;
    }
    else if ((comp = strcmp(str, ptr->word)) == 0)
        ++ptr->count;
    else if (comp < 0)
        ptr->left = addtree(ptr->left, str);
    else
        ptr->right = addtree(ptr->right, str);
    return ptr;
}

void printn(char *s, int n)
{
    putchar('\n');
    for(char *p = s; *p && p < s + n; ++p)
        putchar(*p);
    printf(": ");
}

void treeprint(struct tnode *ptr)
{
    static struct tnode *prev = NULL;
    if (ptr != NULL)
    {
        treeprint(ptr->left);
        if((prev == NULL) || (strncmp(prev->word, ptr->word, complen) != 0))
            printn(ptr->word, complen);
        prev = ptr;
        printf("%s %d ", ptr->word, ptr->count);
        treeprint(ptr->right);
    }
}

void treefree(struct tnode *ptr)
{
    if (ptr != NULL)
    {
        treefree(ptr->left);
        free(ptr->word);
        treefree(ptr->right);
    }
    free(ptr);
}

int readparams(int argc, char *argv[])
{
    int c;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
        {
            switch (c)
            {
            default:
                printf("tail: nieznana opcja %c\n", c);
                argc = 0;
                break;
            }
        }
    if (argc == 1)
    {
        if (isdigit(**argv))
        {
            complen = atoi(*argv);
            --argc;
        }
    }
    if (argc)
    {
        printf("format wywolania: vargroups [liczba liter]\n");
        return 0;
    }
    return 1;
}

int binsearch(char *s, char *tab[], int n)
{
    int low = 0, high = n - 1, mid;
    int cmp = 0;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if((cmp = strcmp(s, tab[mid])) < 0)
            high = mid - 1;
        else if (cmp > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}