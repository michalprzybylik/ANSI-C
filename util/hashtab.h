#define HASHSIZE 1001
#define HASHKEY 31

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

unsigned int hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);
void undefall(void);