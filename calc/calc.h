#define NUMBER '0'
#define FUN 'F'

void fun(char s[]);
double inv(double f);

int getch(void);
void ungetch(int c);
void ungets(char s[]);

int getop(char s[]);

void push(double f);
double pop(void);
double top(void);
void swap(void);
void dstack(void);
void clear(void);