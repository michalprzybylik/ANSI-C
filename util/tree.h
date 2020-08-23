struct tnode
{
    int val;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *ptr, int val);
void treeprint(struct tnode *ptr);
void treefree(struct tnode *ptr);
