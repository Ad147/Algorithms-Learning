// Exercise1-12.c
// Ad
// Write a program that prints its input one word per line.

#include <stdio.h>

// unable to deal with multiple spaces
int main()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
            putchar('\n');
        else
            putchar(c);
    }

    return 0;
}
