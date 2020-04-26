/*
** Exercise1.20.c
** Ad
** Init: 191010
*/

#include <stdio.h>

#define BLANK_NUMBER 4

/* Replaces tabs in input with blanks. */
main()
{
    int c;

    while ((c = getchar()) != EOF)
        if (c == '\t')
            for (int i = 0; i < BLANK_NUMBER; ++i)
                putchar(' ');
        else
            putchar(c);
}
