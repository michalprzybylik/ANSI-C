/*
Ćwiczenie 3.2. Napisz funkcję escape(s,t), która przepisując tekst z argumentu 
t do s, zamienia takie znaki, jak znak nowego wiersza czy tabulacji, na czytelne 
sekwencje specjalne, np. \n i \t. Zastosuj instrukcję switch. Napisz także funkcję 
działającą w odwrotnym kierunku, tzn. przy kopiowaniu zamieniającą sekwencje 
specjalne na rzeczywiste znaki.
*/
#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
    char str[] = "abc\\\n\tcde";
    char str1[] = "";
    char str2[] = "";
    printf("%s\n", str);
    escape(str1, str);
    printf("%s\n", str1);
    unescape(str2, str1);
    printf("%s\n", str2);
    return 0;
}

void escape(char s[], char t[])
{
    int i = 0, j = 0;
    while (t[i])
    {
        switch (t[i])
        {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
        ++i;
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i = 0, j = 0;
    while (t[i])
    {
        if (t[i] == '\\')
            switch (t[i + 1])
            {
            case 'n':
                s[j++] = '\n';
                i += 2;
                break;
            case 't':
                s[j++] = '\t';
                i += 2;
                break;
            default:
                s[j++] = t[i++];
                break;
            }
        else
            s[j++] = t[i++];
    }
    s[j] = '\0';
}