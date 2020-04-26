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
- [6.7 Typedef](#67-typedef)
- [6.9 Bit-fields](#69-bit-fields)

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

```cxx
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

```cxx
struct tnode {              /* the tree node: */
    char *word;             /* points to the text */
    int count;              /* number of occurrence */
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};
```

Occasionally, one needs a variation of self-referential structures:  
2 structures that refer to each other:

```cxx
struct t {
    ...
    struct s *p;    /* p points to an s */
};
struct s {
    ...
    struct t *q;    /* q points to a t */
}
```

```cxx
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

```cxx
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

```cxx
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

```cxx
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

A typical symble table management routines of a macro processor or a compiler.

The algorithm is a hash search, the hash value is used to index into an array of pointers,  
the array element points to a linked list of structures describing names and replacement text of a #define.

```cxx
struct nlist {              /* table entry: */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* defined name */
    char *defn;             /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];     /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;    /* a short and effective hash func */
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  /* found */
    return NULL;        /* not found */
}

char *strdup(char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else      /* already there */
        free((void *)np->defn);     /* free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}
```

6.7 Typedef
--------------------------------------------------------------------------------

```cxx
typedef struct tnode *Treeptr;

typedef struct tnode {  /* the tree node: */
    char *word;             /* points to the text */
    int count;              /* number of occurrences */
    Treeptr left;           /* left child */
    Treeptr right;          /* right child */
} Treenode;

Treeptr talloc(void)
{
    return (Treeptr) malloc(sizeof(Treenode));
}
```

In effect, `typedef` is like `#define`, except that since it is interpreted by compiler, it can cope with textual substitutions that are beyond the capabilities of the preprocessor:

`typedef int (*PFI)(char *, char*);`

creates the PFI (pointer to function (of 2 char * arguments) returning int), which can be used in contexts like `PFI strcmp, numcmp;` in the sort program of ch5.

Three main reasons for using `typedef`:

1. aesthtic issues.
2. parameterize a program against protability problems  
   (if `typedef`s are used for machine-dependent data types, only them need change when program is moved)  
   (like `size_t`, `ptrdiff_t`)
3. easier to understand when introduced in documentations.

6.9 Bit-fields
--------------------------------------------------------------------------------

The usual way is to define a set of masks:

```cxx
#define KEYWORD 01
#define EXTERNAL 02
#define STATIC 04

/* or */

enum { KEYWORD = 01, EXTERNAL = 02, STATIC = 04 };

/* The numbers must be powers of 2. */

/* turns on the EXTERNAL and STATIC bits in flags: */
flags |= EXTERNAL | STATIC;

/* turns them off: */
flags &= ~(EXTERNAL | STATIC);

/* test if both are off: */
if ((flags & (EXTERNAL | STATIC)) == 0) ...
```

##### *bit-field* (*field* for short)

C offers defining and accessing fields within a word directly rather than by bitwise logical operators.

For example, the `#define`s above could be replaced by the definition of 3 fields:

```cxx
struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern  : 1;
    unsigned int is_static  : 1;
} flags;

/* The number following the colon represents the field width in bits. */

/* turn the bits on: */
flags.is_extern = flags.is_static = 1;
/* turn them off: */
flags.is_extern = flags.is_static = 0;
/* test them */
if (flags.is_extern == 0 && flags.is_static == 0)
```

> Almost everything about fields is implementation-dependent.  
> Whether a field may overlay a word boundary is implementation-dependent.  
> Fields need not be names; unnamed fields (a colon and width only) are used for padding.  
> The special width 0 may be used to force alignment at the next word boundary.
> 
> Fields are assigned left to right on some machines and right to left on others.  
> This means that although fields are useful for maintaining internally-defined data structures, the question of which end comes first has to be carefully considered when picking apart externally-defined data;  
> programs that depend on such things are not portable.  
> Fields may be declared only as ints; for portability, specify signed or unsigned explicitly.  
> They are not arrays, and they do not have addresses, so the & operator cannot be applied to them.

--------------------------------------------------------------------------------

EOF
