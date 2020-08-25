struct lnode
{
    int val;
    struct lnode *next;
};

struct lnode *lalloc(void);
struct lnode *addlist(struct lnode *, int);
void listprint(struct lnode *);
void listfree(struct lnode *);