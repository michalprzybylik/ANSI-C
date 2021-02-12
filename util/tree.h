struct tnode
{
    int val;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *ptr, int val);
void printtree(struct tnode *ptr);
void freetree(struct tnode *ptr);
struct tnode *searchtree(struct tnode *ptr, int val);
struct tnode *mintnode(struct tnode *ptr);
struct tnode *maxtnode(struct tnode *ptr);
