#include<stdio.h>

#define LIMIT 10

int main()
{
	int expr = 1;
	int lim = LIMIT;
	char c;
	char s[LIMIT];
	int i = 0;
	while (expr)
	{
		if (i < lim - 2)
		{
			if ((c = getchar()) != '\n')
			{
				if (c != EOF)
				{
					s[i] = c;
					++i;
				}
				else
					expr = 0;
			}
			else
				expr = 0;
		}
		else
			expr = 0;
	}
}