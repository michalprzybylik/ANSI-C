struct lnode
{
    int val;
    struct lnode *next;
};

struct lnode *lalloc(void);
struct lnode *appendlist(struct lnode *, int);
struct lnode *addflist(struct lnode *, int);
void listprint(struct lnode *);
void listfree(struct lnode *);