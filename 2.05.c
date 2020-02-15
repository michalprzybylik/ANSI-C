#include<stdio.h>

int any(char s1[], char s2[]);

int main()
{
	char string1[] = "abwefmwqwmeiqqrqbac";
	char string2[] = "mew";;
	printf("%d\n", any(string1, string2));
	return 0;
}

int any(char s1[], char s2[])
{
	int i, j;
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
        {
		    if (s2[j] == s1[i])
			    return i;
        	++j;
        }
		++i;
	}
	return -1;
}