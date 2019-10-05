/*
** Exercise1.10.c
** Ad
** Init: 191003
*/

#include <stdio.h>

/* Copy input to output with tab replaced by \t, backspace replaced by \b, and backslash replaced by \\. */
main()
{
    int c;

    while ((c = getchar()) != EOF)
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else
            putchar(c);
}
