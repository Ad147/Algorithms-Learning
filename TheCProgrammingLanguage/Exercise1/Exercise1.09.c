/*
** Exercise1.09.c
** Ad
** Init: 191003
*/

#include <stdio.h>

/* Copy input to output with multiple blanks replaced by single. */
main()
{
    int c, pc;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' && pc == ' ')
            continue;

        pc = c;
        putchar(c);
    }
}
