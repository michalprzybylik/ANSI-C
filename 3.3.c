#include<stdio.h>

#define MAXTAB 1000

void expand(char s1[], char s2[]);

int main(void)
{
	char str0[MAXTAB] = "a-z";
	char str1[MAXTAB] = "a-b-c";
	char str2[MAXTAB] = "a-z0-9";
	char str3[MAXTAB] = "-a-z";
	char expstr0[MAXTAB] = "";
	char expstr1[MAXTAB] = "";
	char expstr2[MAXTAB] = "";
	char expstr3[MAXTAB] = "";
	expand(str0, expstr0);
	expand(str1, expstr1);
	expand(str2, expstr2);
	expand(str3, expstr3);
	printf("%s %s\n", str0, expstr0);
	printf("%s %s\n", str1, expstr1);
	printf("%s %s\n", str2, expstr2);
	printf("%s %s\n", str3, expstr3);
	return 0;
}

void expand(char s1[] , char s2[])
{
	char c;
	int i = 0, j = 0;
	while((c = s1[i++]))
		if(s1[i] == '-' && s1[i + 1] >= c)
		{
			++i;
			while(c < s1[i])
				s2[j++] = c++;
		}
		else
			s2[j++] = c++;
	s2[j] = '\0';
}
