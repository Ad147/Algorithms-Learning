TCPL5-PtrsArrays.md

TCPL Notes 5: Pointers & Arrays
================================================================================

AL~0a30

--------------------------------------------------------------------------------

- [5.1 Pointers & Addresses](#51-pointers--addresses)
- [5.2 Pointers & Function Arguments](#52-pointers--function-arguments)
- [5.3 Pointers & Arrays](#53-pointers--arrays)
- [5.4 Address Arithmatic](#54-address-arithmatic)
- [5.5 Character Pointers & Functions](#55-character-pointers--functions)

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

p118