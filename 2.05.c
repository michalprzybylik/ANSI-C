/*
Ćwiczenie 2.5. Napisz funkcję any(s1,s2), która zwraca albo pozycję pierwszego 
wystąpienia dowolnego znaku z s2 w tekście argumentu s1, albo -1, jeśli tekst 
w s1 nie zawiera żadnego znaku z s2. (Standardowa funkcja biblioteczna strpbrk 
wykonuje to samo zadanie, ale zwraca wskaźnik do znalezionej pozycji.)
*/
#include <stdio.h>

int any(char s1[], char s2[]);

int main()
{
	char string1[] = "abwefmwqwmeiqqrqbac";
	char string2[] = "mew";
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