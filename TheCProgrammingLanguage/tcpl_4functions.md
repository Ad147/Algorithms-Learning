tcpl_4functions.md

The C Programming Language
================================================================================

Laer

Init: 191030

Chapter 4: Functions & Program Structure
--------------------------------------------------------------------------------

- [Chapter 4: Functions & Program Structure](#chapter-4-functions--program-structure)
  - [4.1 Basics of Functions](#41-basics-of-functions)
  - [4.2 Functions Returning Non-integers](#42-functions-returning-non-integers)
  - [4.3 External Variables](#43-external-variables)
  - [4.4 Scope Rules](#44-scope-rules)
  - [4.5 Header Files](#45-header-files)
  - [4.6 Static Variables](#46-static-variables)
  - [4.7 Register Variables](#47-register-variables)
  - [4.8 Block Structure](#48-block-structure)
  - [4.9 Initialization](#49-initialization)
  - [4.10 Recursion](#410-recursion)
  - [4.11 The C Preprocessor](#411-the-c-preprocessor)

--------------------------------------------------------------------------------

### 4.1 Basics of Functions

3 pieces are easier to deal with than 1 big one.

```cs
#include <stdio.h>
#define MAXLINE 1000    /* maximum input line length */

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";    /* pattern to search for */

/* find all lines matching pattern */
main()
{
    char line[MAXLINE];
    int found = 0;

    while (getline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0)
        {
            printf("%s", line);
            found++;
        }
    return found;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++)
    {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}
```

--------------------------------------------------------------------------------

### 4.2 Functions Returning Non-integers

```cs
#include <ctype.h>

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}
```

```cs
#include <stdio.h>

#define MAXLINE 100

/* rudimentary calculator */
main()
{
    double sum, atof(char []);
    char line[MAXLINE];
    int getline(char line[], int max);

    sum = 0;
    while (getline(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));
    return 0;
}
```

```cs
/* atoi: convert string s to integer using atof */
int atoi(char s[])
{
    double atof(char s[]);

    return (int) atof(s);
}
```

--------------------------------------------------------------------------------

### 4.3 External Variables

- Internal: arguments & variables defined inside functions
- External: defined outside of any function

```cs
/* structure of reverse Polish calculator */
while (next operator or operand is not end-of-file indicator)
    if (number)
        push it
    else if (operator)
        pop operands
        do operation
        push result
    else if (newline)
        pop & print top of stack
    else error
```

```cs
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
```

```cs
#define MAXVAL  100     /* maximum depth of val stack */

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, cannot push %g\n", f);
}


/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}
```

```cs
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    i = 0;
    if (isdigit(c))     /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
```

```cs
#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
```

--------------------------------------------------------------------------------

### 4.4 Scope Rules

### 4.5 Header Files

### 4.6 Static Variables

External `static` limits the scope of an object to the rest of the source file

Internal `static` variables provide private, permanent storage within a single function

--------------------------------------------------------------------------------

### 4.7 Register Variables

### 4.8 Block Structure

### 4.9 Initialization

```cs
int x = 1;
int days[] = { 1, 2, 3 };
char s[] = "Hello";
```

--------------------------------------------------------------------------------

### 4.10 Recursion

```cs
#include <stdio.h>

/* printd: print n in decimal */
void printd(int n)
{
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}
```

```cs
/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int  v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)      /* do nothing if array contains */
        return;             /* fewer than 2 elements */
    swap(v, left, (left + right)/2)     /* move partition elem to v[0] */
    last = left;
    for (i = left+1; i <=right; i++)    /* partition */
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);    /* restore partition elem */
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}
```

```cs
/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
```

--------------------------------------------------------------------------------

### 4.11 The C Preprocessor

#### 4.11.1 File Inclusion

#### 4.11.2 Macro Substitution

```c
#define max(A, B)   ((A) > (B) ? (A) : (B))
```

Names may be undefined with `#undef`, usually to ensure that a routine is really a function, not a macro:

```c
#undef getchar

int getchar(void) {...}
```

```cs
#define dprint(expr)    printf(#expr " = %g\n", expr)

/* then, the expression */
dprint(x/y);
/* becomes */
printf("x/y" " = %g\n", x/y);
/* and the effect is */
printf("x/y = %g\n", x/y);
```

```cs
#define paste(front, back)  front ## back

/* so */
paste(name, 1)
/* creates the token */
name1
```

#### 4.11.3 Conditional Inclusion

```cs
#if !defined(HDR)
/* or */
#ifndef HDR

#define HDR

/* contents of hdr.h go here */

#endif
```

`#elif` `#else`

--------------------------------------------------------------------------------

EOF
