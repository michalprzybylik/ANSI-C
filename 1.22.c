#include <stdio.h>

#define MAXLINE 1000
#define N 30
#define TABSIZE 8

int getLine(char line[], int lim);
int sizeLine(char line[]);
int findBeforeN(char line[], int n);
void cutLine(char line[], char line1[], char line2[], int n);
int deleteBlank(char to[], char from[]);
void deTab(char to[], char from[]);

int main()
{
	int line_size;
	char rawline[MAXLINE];
	char line[MAXLINE];
	char line1[MAXLINE];
	char line2[MAXLINE];
	int pos;
	while ((getLine(rawline, MAXLINE)) != 0)
	{
		deTab(line, rawline);
		while (sizeLine(line) > 0)
		{
			pos = findBeforeN(line, N);
			cutLine(line, line1, line2, pos);
			deleteBlank(line, line2);
			if(sizeLine(line1) > 0)
				printf("%s", line1);
		}
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

int findBeforeN(char line[], int n)
{
	int i;
	i = 0;
	while (line[i] != '\0')
		i++;
	if (i >= n)
		i = n - 2;
	else
		i = i - 2;
	while (i > 0 && (line[i] == ' ' || line[i] == '\t'))
		--i;
	return i;
}

void cutLine(char line[], char line1[], char line2[], int n)
{
	int i, j, k;
	i = j = k = 0;
	while (line[k] != '\0')
		++k;
	while (i <= n)
	{
		line1[i] = line[i];
		++i;
	}
	line1[i] = '\n';
	line1[i + 1] = '\0';
	while ((line2[j] = line[j + i]) != '\0')
		++j;
}

int deleteBlank(char to[], char from[])
{
	int i = 0, j = 0;
	while (from[j] == ' ' || from[j] == '\t' || from[j] == '\n')
		++j;
	while ((to[i] = from[i + j]) != '\0')
		++i;
	return i;
}

int sizeLine(char line[])
{
	int i;
	for (i = 0; line[i] != '\0'; ++i)
		;
	return i;
}

void deTab(char to[], char from[])
{
	int i, j, pos, toadd;
	i = j = pos = 0;
	while (from[i] != '\0')
	{
		if (pos > TABSIZE - 1)
			pos = 0;
		if (from[i] == '\t')
		{
			toadd = TABSIZE - pos;
			int k;
			for (k = 0; k < toadd; ++k)
				to[j + k] = ' ';
			j = j + k - 1;
			pos = 0;
		}
		else
		{
			to[j] = from[i];
			++pos;
		}
		++i;
		++j;
	}
	to[j] = '\0';
}