#include <stdio.h>
int i;
	int z = 1;
int main()
{
	void inc (void);
	int z = 1;
	inc();
	char z1 = 127;
	i = 0;
	short int z2 = 32767;
	printf("%d\n", z1 + z2);
	int fun (char);
	char a;
	char b;
	char *pa = &a;
	fun(1);
	char *pat = &b;
	int c = pat - pa; 
	fun(4);
	fun(2);
	printf("%p\n", pa);
	printf("%p\n", pat);
	printf("%d\n", pa > pat ? 1 : 0);
	int num;
	scanf("%d", &num);
	int tab[num];
	for(int i = 0; i < num; i++)
	{
		scanf("%d", tab + i);
	}
	for(int i = 0; i < num; i++)
		printf ("%d ", *(tab + i) * 2);
	int la = 0, lb = 4;
	printf("\n%d\n", la / lb);
	printf("\n%d\n", la % lb);
	int i = 0;
	printf("%d\n", i = 1 && 0);
	printf("%d\n", i);
	i = 12;
	i = a = 12;
	i = a++;
	printf("%d\n", i);
	printf("z=%d\n", z);
	inc();
	printf("z=%d\n", z);
	i = 0;
	if (i = 1 && ++i == 1) //ciekawe
		printf("tu i=%d\n", i);
	if ((i = 1) && (++i == 2) && (i++ == 2) && (i == 3)) //ciekawe
		printf("i=%d\n", i);
	return 0;
	
}

int fun(char a)
{
	char b;
	char c;
	c = b;
	b = c;
	printf("%p\n", &b);
	return a; 	
}

void inc(void)
{
	extern int z;
	z++;
}
