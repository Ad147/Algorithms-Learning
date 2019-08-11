// Exercise1-19.c
// Ad
// Write a function reverse(s) that reverses the character string s.
// Use it to write a program that reverses its input a line at a time.

#include <stdio.h>

void reverse(char s[]);
int getline(char s[], int lim);
void copy(char to[], char from[]);

int main()
{
    char line[100];
    getline(line, 100);
    reverse(line);
    printf("%s", line);
}

void reverse(char s[])
{
    int sz;
    for (sz = 0; s[sz] != '\0'; ++sz)
        ;
    --sz;
    char r[100];
    int i;
    for (i = 0; i < sz; ++i)
        r[i] = s[sz - i - 1];

    copy(s, r);
}

int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
