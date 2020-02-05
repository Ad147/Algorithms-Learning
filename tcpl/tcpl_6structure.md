tcpl_6structure.md

TCPL Notes: 6 Structures
================================================================================

A~0b04

--------------------------------------------------------------------------------

- [6.1 Basics of Structures](#61-basics-of-structures)
- [6.2 Structures and Functions](#62-structures-and-functions)
- [6.3 Arrays of Structures](#63-arrays-of-structures)
- [6.4 Pointers to Structures](#64-pointers-to-structures)

6.1 Basics of Structures
--------------------------------------------------------------------------------

Declaration: `struct point { int x; int y; };`

Instance definition: `struct point pt;`

6.2 Structures and Functions
--------------------------------------------------------------------------------

Ops on a structure:

1. copy/assignment
2. taking its address
3. accesing members

6.3 Arrays of Structures
--------------------------------------------------------------------------------

The `sizeof` operator:

`sizeof object` / `sizeof(type name)`

(the object can be a variable, array or structure)

```cpp
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
    char *word;
    int count;
} keytab[] = {
    { "auto", 0 },
    { "break", 0 },
    /* ... */
    { "while", 0 }
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            print("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}
```

6.4 Pointers to Structures
--------------------------------------------------------------------------------

p150