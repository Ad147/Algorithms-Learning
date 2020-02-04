tcpl_3controlflow.md

Notes of The C Programming Language
================================================================================

Ad

Init: 191016

Chapter 3: Control Flow
--------------------------------------------------------------------------------

- [Chapter 3: Control Flow](#chapter-3-control-flow)
  - [3.1 Statements and Blocks](#31-statements-and-blocks)
  - [3.2 If-Else](#32-if-else)
  - [3.3 Else-If](#33-else-if)
  - [3.4 Switch](#34-switch)
  - [3.5 Loops - While and For](#35-loops---while-and-for)
  - [3.6 Loops - Do-while](#36-loops---do-while)
  - [3.7 Break and Continue](#37-break-and-continue)
  - [3.8 Goto and Labels](#38-goto-and-labels)

--------------------------------------------------------------------------------

### 3.1 Statements and Blocks

Semicolon: a statement terminator  
Braces `{}`: group into *compound statement* / *block*

--------------------------------------------------------------------------------

### 3.2 If-Else

### 3.3 Else-If

```cs
/* binsearch: find x in v[0] <= v[1] <= ... <=v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    hight = n - 1;
    while (low <= high)
    {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    return -1;  /* no match */
}
```

--------------------------------------------------------------------------------

### 3.4 Switch

Putting a `break` after the last case will save you when another case gets added.

--------------------------------------------------------------------------------

### 3.5 Loops - While and For

```cs
/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap)
            {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}
```

```cs
#include <string.h>

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
```

The commas that separate function arguments, variables in declarations, etc., are *not* comma operators, and do not guarantee left to right evaluation.

Comma operators should be used sparingly.  
The most suitable uses are for constructs strongly related to each other, as in the `for` loop in reverse,  
and in macros where a multistep computation has to be a single expression.  
A comma experssion might also be appropriate for the exchange of elements in reverse, where the exchange can be thought of as a single operation:  

```cs
for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
```

--------------------------------------------------------------------------------

### 3.6 Loops - Do-while

```cs
/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)         /* record sign */
        n = -n;                 /* make n positive */
    i = 0;
    do {                        /* generate digits in reverse order */
        s[i++] = n % 10 + '0';  /* get next digit */
    } while ((n /= 10) > 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
```

--------------------------------------------------------------------------------

### 3.7 Break and Continue

A `break` causes the innermost enclosing loop or switch to be exited.

```cs
/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[])
{
    int n;

    for (n = strlen(s)-1; n >= 0; n--)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
    return n;
}
```

--------------------------------------------------------------------------------

### 3.8 Goto and Labels

```cs
for (...)
    for(...)
    {
        ...
        if (disaster)
            goto error;
    }
...

error:
    clean up the mess
```

--------------------------------------------------------------------------------

EOF
