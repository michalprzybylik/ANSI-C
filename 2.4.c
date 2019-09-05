#include<stdio.h>

void squezze(char s1[], char s2[]);

int main()
{
	char string1[] = "abwefmwqwmei  qqrqbac";
	char string2[] = "bc";
	squezze(string1, string2);
	printf("%s\n", string1);
	return 0;
}

void squezze(char s1[], char s2[])
{
	int i, j, k;
	i = k = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j] && s2[j] != s1[i])
			++j;
		if (!s2[j])
			s1[k++] = s1[i];
		++i;
	}
	s1[k] = '\0';
}