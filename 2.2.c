#define LIMIT 10

int expr=1;
int lim = LIMIT;
int i = 0;
char s[LIMIT];

while(expr)
{
	if(i<lim-2)
	{
		if((c=getchar()) != '\n')
		{
			if(c!=EOF)
			{
				s[i]=c;
				++i;
			}
			else
				expr=0;
		}
		else
			expr=0;
	}
	else
		expr=0;
}
