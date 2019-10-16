TCPL3-ControlFlow.md

Notes of The C Programming Language
================================================================================

Ad

Init: 191016

Chapter 3: Control Flow
--------------------------------------------------------------------------------

- [3.1 Statements and Blocks](#31-statements-and-blocks)
- [3.2 If-Else](#32-if-else)
- [3.3 Else-If](#33-else-if)
- [3.4 Switch](#34-switch)
- [3.5 Loops - While and For](#35-loops---while-and-for)

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
}