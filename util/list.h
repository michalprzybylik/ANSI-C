#include <stdbool.h>

typedef struct lnode
{
    int val;
    struct lnode *next;
} Listnode;

typedef Listnode* Nodeptr;

Nodeptr nodealloc(void);
Nodeptr appendlist(Nodeptr*, int);
Nodeptr addlist(Nodeptr*, int);
Nodeptr findlist(Nodeptr, int); 
void printlist(Nodeptr);
void removenode(Nodeptr*, int);
void freelist(Nodeptr);