struct quelem 
{
    int val;
    struct quelem *prev;
};

struct queue
{
    struct quelem *head;
    struct quelem *tail;
};

struct queue *quealloc(void);
bool emptyque(struct queue *que);
struct queue *enque(struct queue *que, int val);
int first(struct queue *que);
int deque(struct queue *que);
void printque(struct queue *que);