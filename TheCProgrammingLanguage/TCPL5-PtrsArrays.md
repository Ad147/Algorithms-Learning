TCPL5-PtrsArrays.md

TCPL Notes 5: Pointers & Arrays
================================================================================

A~0a30

--------------------------------------------------------------------------------

- [5.1 Pointers & Addresses](#51-pointers--addresses)
- [5.2 Pointers & Function Arguments](#52-pointers--function-arguments)
- [5.3 Pointers & Arrays](#53-pointers--arrays)
- [5.4 Address Arithmatic](#54-address-arithmatic)
- [5.5 Character Pointers & Functions](#55-character-pointers--functions)
- [5.6 Pointer Arrays; Pointers to Pointers](#56-pointer-arrays-pointers-to-pointers)
- [5.7 Multi-dimensional Arrays](#57-multi-dimensional-arrays)
- [5.9 Pointers vs. Multi-dimensional Arrays](#59-pointers-vs-multi-dimensional-arrays)
- [5.10 Command-line Arguments](#510-command-line-arguments)
- [5.11 Pointers to Functions](#511-pointers-to-functions)

5.1 Pointers & Addresses
--------------------------------------------------------------------------------

5.2 Pointers & Function Arguments
--------------------------------------------------------------------------------

Pointers enable a function to return status as its function value, and the actual value using pointer.

```cpp
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))    /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        unget(c);
    return c;
}
```

5.3 Pointers & Arrays
--------------------------------------------------------------------------------

One difference between an array name and a pointer:

- a pointer is a variale ==> pa = a, pa++
- an array name is not ==> a = pa (x), a++ (x)

5.4 Address Arithmatic
--------------------------------------------------------------------------------

 Legal:

 1. ip1 = ip2
 2. p +/- i
 3. subtracting or comparing 2 ptrs to members of the same array
 4. p =/< 0 (NULL)

Illegal:

1. assigning a ptr of one type to a ptr of another type without a cast (except for void*)
2. p + f
3. p1 + p2

5.5 Character Pointers & Functions
--------------------------------------------------------------------------------

`char *pmsg = "hello world";`
assigns to pmsg a pointer to the character array.

An important difference between the 2 definitions:

```c
char amsg[] = "hello world";    /* an array */
char *pmsg = "hello world";     /* a pointer */
```

amsg is an array, individual chars within the array may be changed,
but amsg always refer to the same storage.  
pmsg is a pointer, may be modified to point elsewhere,
but the result of modifying the string contents is undefined.

```cpp
/* strcpy: copy t to s; pointer version 3 */
void strcpy(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}
```

```cpp
/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *s, char *t)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}
```

The standard idioms for pushing & popping a stack:

```c
*p++ = val;     /* push val onto stack */
val = *--p;     /* pop top of stack into val */
```

5.6 Pointer Arrays; Pointers to Pointers
--------------------------------------------------------------------------------

Example: a program to sort lines of strings using quicksort.

5.7 Multi-dimensional Arrays
--------------------------------------------------------------------------------

- `daytab[i][j]` (v)
- `daytab[i, j]` (x)

```cpp
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
```

As a function parameter:

```cpp
func(int daytab[2][13]) { ... }
func(int daytab[][13]) { ... }
func(int (*daytab)[13]) { ... }
```

5.9 Pointers vs. Multi-dimensional Arrays
--------------------------------------------------------------------------------

`int a[10][20]`: 2 dimensional array with 200 int-sized locations.

`int *b[10]`: 10 pointers, each can point to array of different length.

5.10 Command-line Arguments
--------------------------------------------------------------------------------

Arguments of `main`:

1. `argc`: argument count
2. `argv`: argument vector

By convention, argv[0] is the name by which the program was invoked, so argc is at least 1.  
The standard requires that argv[argc] be a null pointer.

```cpp
#include <stdio.h>

/* echo command-line arguments */
main(int argc, char *argv[])
{
    while (--argc > 0)
        printf((argc > 1) ? "%s " : "%s", *++argv);
    printf("\n");
    return 0;
}
```

###### Enhancement of the pattern-finding program from Section 4.1

```cpp
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);

/* find: print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
    char line[MAXLINE];
    int found = 0;

    if (argc != 2)
        print("Usage: find pattern\n");
    else
        while (getline(line, MAXLINE) > 0)
            if (strstr(line, argv[1]) != NULL)
            {
                printf("%s", line);
                found++;
            }
    return found;
}
```

A common convention for C program on UNIX systems:  
`-xxx` for optional flag or parameter:

`find -x -n pattern`  
`find -nx pattern`

```cpp
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

ine getline(char *line, int max);

/* find: print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
    char lien[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c)
            {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    print("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
    if (argc != 1)
        printf("Usage: find -x -n pattern\n");
    else
        while (getline(line, MAXLINE) > 0)
        {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except)
            {
                if (number)
                    printf("%ld:", lineno);
                printf(%s, line);
                found++;
            }
        }
    return found;
}
```

5.11 Pointers to Functions
--------------------------------------------------------------------------------

p133