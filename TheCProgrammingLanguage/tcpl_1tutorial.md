tcpl_1tutorial.md

TCPL Notes 1 A Tutorial Introduction
================================================================================

A~-2k19

--------------------------------------------------------------------------------

- [1.1 Getting Started](#11-getting-started)
- [1.2 Variables and Arithmetic Expressions](#12-variables-and-arithmetic-expressions)
- [1.3  The For Statement](#13-the-for-statement)
- [1.4 Symbolic Constants](#14-symbolic-constants)
- [1.5 Character Input and Output](#15-character-input-and-output)
  - [1.5.1 File Copying](#151-file-copying)
  - [1.5.2 Character Counting](#152-character-counting)
  - [1.5.3 Line Counting](#153-line-counting)
  - [1.5.4 Word Counting](#154-word-counting)
- [1.6 Arrays](#16-arrays)
- [1.7 Functions](#17-functions)
- [1.8 Arguments - Call by Value](#18-arguments---call-by-value)
- [1.9 Character Arrays](#19-character-arrays)
- [1.10 External Variables and Scope](#110-external-variables-and-scope)

1.1 Getting Started
--------------------------------------------------------------------------------

HelloWorld:

```cxx
#include <stdio.h>           /* include information about standard library */

main()                       /* define a function named main that receives no argument values */
{                            /* statements of main are enclosed in braces */
    printf("Hello World\n"); /* main calls library function printf to print this sequence of characters; \n represents the newline character */
}
```

1.2 Variables and Arithmetic Expressions
--------------------------------------------------------------------------------

Fahrenheit <-> centigrade/Celsius convertor: (C = (5/9)(F - 32))

```cxx
#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300 */
main()
{
    float fahr, celsius;    /* Variables usually declared at the beginning of */
    int lower, upper, step; /* the function before any executable statements. */

    lower = 0;              /* lower limit of temperature table */
    upper = 300;            /* upper limit */
    step = 20;              /* step size */

    fahr = lower;
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius); /* %6.1f: >= 6 wide (right justified), 1 after decimal. */
        fahr = fahr + step;
    }
}
```

1.3  The For Statement
--------------------------------------------------------------------------------

`for` is appropriate when initialization and increment are single statements and logically related.

```cxx
main()
{
    int fahr;

    for (fahr = 0; fahr <= 300; fahr = fahr + 20) /* magic numbers is a bad practice */
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
```

1.4 Symbolic Constants
--------------------------------------------------------------------------------

`#define` defines a *symbolic name* or *symbolic constant* to be a string of characters:  
`#define name replacement text`

```cxx
#define LOWER 0
#define UPPER 300
#define STEP  20
```

1.5 Character Input and Output
--------------------------------------------------------------------------------

`getchar()`  
`putchar()`

### 1.5.1 File Copying

```cxx
#include <stdio.h>

/* copy input to output; 2nd version */
main()
{
    int c; /* EOF cannot be held by char */

    while ((c = getchar()) != EOF)
        putchar(c);
}
```

### 1.5.2 Character Counting

```cxx
#include <stdio.h>

/* count characters in input; 2nd version */
main()
{
    double nc;
    
    for (nc = 0; getchar != EOF; ++nc)
        ;
    printf("%.0f\n", nc);
}
```

### 1.5.3 Line Counting

```cxx
#include <stdio.h>

/* count lines in input */
main()
{
    int c, nl;

    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);
}
```

### 1.5.4 Word Counting

```cxx
#include <stdio.h>

#define IN 1    /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */
main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT)
        {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}
```

1.6 Arrays
--------------------------------------------------------------------------------

Digit counting with an array:

```cxx
#include <stdio.h>

/* count digits, white space, others */
main()
{
    int c, i, nwhite, nother;
    int ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++other;

    printf("digits =");
    for (i = 0; i < 10; ++i)
        printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);
}
```

1.7 Functions
--------------------------------------------------------------------------------

```cxx
#include <stdio.h>

int power(int m, int n);

/* test power function */
main()
{
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2, i), power(-1, i));
    return 0;
}

/* power: raise base to n-th power; n >= 0 */
int power(int base, int n)
{
    int i, p;

    p = 1;
    for (i = 1; i < n; ++i)
        p = p * base;
    return p;
}
```

- *parameter*(formal argument): a variable named in the parenthesized list in a function definition
- *argument*(actual argument): the value used in a call of thefunction
- *function prototype*: declaration before main

1.8 Arguments - Call by Value
--------------------------------------------------------------------------------

When to use ptr: to modify a variable of calling function in the called function.

Arrays are passed by address.

1.9 Character Arrays
--------------------------------------------------------------------------------

Every text line has at least 1 character: containing only a newline has length 1.

```cxx
#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
    int len;                /* current line length */
    int max;                /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE]   /* longest line saved here */

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0)
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    if (max > 0)    /* there was a line */
        printf("%s", longest);
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
```

For a `getline` user, no way to know how long an input line might be, so it checks for overflow;  
however a `copy` user knows/can find out how big the strings are, so no error checking added.

1.10 External Variables and Scope
--------------------------------------------------------------------------------

An *external variable* must be *defined*, exactly once, outside of any function, to set storage,  
must also be *declared* in each function that wants to access it, to state the type of the variable.  
The declaration may an explicit `extern` statement or implicit from context.

- **Definition**: where the variable is created or assigned storage
- **declaration**: where the nature of the variable is stated but no storage is allocated

Extern declaration omit: if the definition of an external variable occurs in the source file before its use in a particular function.  
Common practice: place definitions of all external variables at the beginning of the source file, and then omit all extern declarations.

If the program is in several source files, and a variable is defined in file1 and used in file2 and file3, then extern declarations are needed in file2 and file3 to connect the occurrences of the variable.  
Usual practice: collect extern declarations of variables and functions in a separate file, historically called a header, that is included by #include at the front of each source file.

--------------------------------------------------------------------------------

EOF
