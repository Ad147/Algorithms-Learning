tcpl_6structure.md

TCPL Notes: 6 Structures
================================================================================

A~0b04

--------------------------------------------------------------------------------

- [6.1 Basics of Structures](#61-basics-of-structures)
- [6.2 Structures and Functions](#62-structures-and-functions)
- [6.3 Arrays of Structures](#63-arrays-of-structures)
- [6.5 Self-referential Structures](#65-self-referential-structures)
- [6.6 Table Lookup](#66-table-lookup)

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

6.5 Self-referential Structures
--------------------------------------------------------------------------------

BST:

```cpp
struct tnode {              /* the tree node: */
    char *word;             /* points to the text */
    int count;              /* number of occurrence */
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};
```

Occasionally, one needs a variation of self-referential structures:  
2 structures that refer to each other:

```cpp
struct t {
    ...
    struct s *p;    /* p points to an s */
};
struct s {
    ...
    struct t *q;    /* q points to a t */
}
```

```cpp
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);
    return 0;
}
```

```cpp
struct tnode *talloc(void);
char *strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();   /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;     /* repeated word */
    else if (cond < 0)  /* less than into left subtree */
        p->left = addtree(p->left, w);
    else                /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}
```

```cpp
/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}
```

```cpp
#include <stdlib.h>

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)   /* make a duplicate of s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1);   /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
```

6.6 Table Lookup
--------------------------------------------------------------------------------

p157