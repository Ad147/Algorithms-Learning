TCPL1-Introduction.md

Notes of The C Programming Language
================================================================================

Ad

Init: 18Nov19

Chapter 1: A Tutorial Introduction
--------------------------------------------------------------------------------

- [1.1 Getting Started](#11-getting-started)
- [1.2 Variables and Arithmetic Expressions](#12-variables-and-arithmetic-expressions)
- [1.3 The For Statement](#13-the-for-statement)
- [1.4 Symbolic Constants](#14-symbolic-constants)
- [1.5 Character Input and Output](#15-character-input-and-output)
  - [1.5.1 File Copying](#151-file-copying)
  - [1.5.2 Character Counting](#152-character-counting)
  - [1.5.3 Line Counting](#153-line-counting)
  - [1.5.4 Word Counting](#154-word-counting)
- [1.6 Arrays](#16-arrays)
- [1.7 Functions](#17-functions)
- [1.8 Arguments-Call by Value](#18-arguments-call-by-value)
- [1.9 Character Arrays](#19-character-arrays)

--------------------------------------------------------------------------------

### 1.1 Getting Started

HelloWorld:

```cs
#include <stdio.h>           /* include information about standard library */

main()                       /* define a function named main that receives no argument values */
{                            /* statements of main are enclosed in braces */
    printf("Hello World\n"); /* main calls library function printf to print this sequence of characters; \n represents the newline character */
}
```

### 1.2 Variables and Arithmetic Expressions

Fahrenheit <-> centigrade/Celsius temperatures convertor:  
(C = (5/9)(F - 32))

```cs
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

Types:
- int
- float
- char: a single byte
- short
- long
- double

`printf` recognizes
- `%o`: octal
- `%x`: hexadecimal
- `%c`: character
- `%s`: string
- `%%`: % itself

### 1.3  The For Statement

`for` is appropriate when initialization and increment are single statements and logically related.

```cs
main()
{
    int fahr;

    for (fahr = 0; fahr <= 300; fahr = fahr + 20) /* magic numbers is a bad practice */
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
```

### 1.4 Symbolic Constants

`#define` defines a *symbolic name* or *symbolic constant* to be a string of characters:  
`#define name replacement text`

```cs
#define LOWER 0
#define UPPER 300
#define STEP  20
```

### 1.5 Character Input and Output

`getchar()`  
`putchar()`

#### 1.5.1 File Copying

```cs
#include <stdio.h>

/* copy input to output; 2nd version */
main()
{
    int c; /* EOF cannot be held by char */

    while ((c = getchar()) != EOF)
        putchar(c);
}
```

#### 1.5.2 Character Counting

```cs
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

#### 1.5.3 Line Counting

```cs
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

#### 1.5.4 Word Counting

```cs
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

### 1.6 Arrays

digit counting with an array to store the numbers of digits

```c
int ndigit[10];
// init to zeros
while ((c = getchar()) != EOF)
    if (c >= '0' && c <= '9')
        ++ndigit[c-'0']; //  (c-'0') coorrsponds to the number in c
    else
        ...
```

### 1.7 Functions

We will generally use *parameter* for a variable named in the parenthesized list in a function definition, and *argument* for the value used in a call of thefunction.  
The terms *formal argument* and *actual argument* are sometimes used for the same distinction.

### 1.8 Arguments-Call by Value

To modify a variable inside a function, use a pointer.

Arrays are passed by address.

### 1.9 Character Arrays

Zero is an acceptable end-of-file return because it is never a validline length.  
Every text line has at least one character;  
even a line containingonly a newline has length 1.

```c
// getline: read a line into s, return length
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
    s[i] = '\0'; // '\0' the null character, whose value is zero

    return i;
}
```

```c
// copy: copy 'from' into 'to'; assume to is big enough
void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
```

// ### 1.10 External Variables and Scope
