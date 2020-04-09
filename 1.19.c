/*
Ćwiczenie 1.19. Napisz funkcję reverse(s) odwracającą kolejność znaków tekstu
w argumencie s. Zastosuj ją w programie odwracającym kolejno wszystkie
wiersze wejściowe 
*/
#include <stdio.h>

#define MAXLINE 1000

int getLine(char line[], int lim);
void reverse(char to[], char from[]);

int main()
{
	int len, max = 0;
	char line[MAXLINE];
	char reverseline[MAXLINE];

	while (getLine(line, MAXLINE) != 0)
	{
		reverse(reverseline, line);
		printf("%s\n", reverseline);
	}
	return 0;
}

int getLine(char line[], int lim)
{
	int i = 0, c = 0;
	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
		if (i < lim - 1)
			line[i] = c;
	if (c == '\n')
	{
		if (i < lim - 1)
			line[i] = c;
		++i;
	}
	if (i < lim)
		line[i] = '\0';
	else
		line[lim - 1] = '\0';
	return i;
}

void reverse(char to[], char from[])
{
	int i, j = 0;
	while (from[j] != '\0')
		++j;
	if (from[j - 1] == '\n')
		--j;
	for (i = 0; i < j; ++i)
		to[i] = from[j - i - 1];
	to[j] = '\0';
}