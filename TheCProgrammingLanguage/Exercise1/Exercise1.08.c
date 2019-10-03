/*
** Exercise1.08.c
** Ad
** Init: 191003
*/

#include <stdio.h>

/* count blanks, tabs, and newlines in input */
main()
{
    int c, nb, nt, nl;

    nb = nt = nl = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ')
            ++nb;
        else if (c == '\t')
            ++nt;
        else if (c == '\n')
            ++nl;

    printf("%d\n%d\n%d\n", nb, nt, nl);
}
