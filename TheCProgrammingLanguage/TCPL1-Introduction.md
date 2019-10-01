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

`main()` function and assembly:

```cs
main() {}
```

```asm
	.file	"hello.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 7.3.0"
```

```asm
	.file	"hello.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
```

### 1.2 Variables and Arithmetic Expressions

A program prints Fahrenheit temperatures and their centigrade or Celsius equivalents.

types:
 - int
 - float
 - char: a single byte
 - short
 - long
 - double

`printf("%3.0f %6.1f\n", fahr, celsius);`  
 - `%6.1f`: printed at least 6 characters wide (right justified) with 1 digit decimal

other:
 - `%o`: octal
 - `%x`: hexadecimal
 - `%c`: character
 - `%s`: string
 - `%%`: % itself

### 1.3  The For Statement

The `for` is usually appropriate for loops in which the initialization and increment are single statements and logically related.

### 1.4 Symbolic Constants

A `#define` line defines asymbolic name or symbolic constant to be a particular string of characters:  
`#define name replacement text`

```c
#define LOWER 0
#define UPPER 300
#define STEP  20
```

### 1.5 Character Input and Output

`getchar()`  
`putchar()`

#### 1.5.1 File Copying

`while ((c = getchar()) != EOF)`  
`putchar();`

#### 1.5.2 Character Counting

#### 1.5.3 Line Counting

#### 1.5.4 Word Counting

```c
#include <stdio.h>

#define IN 1  // inside a word
#define OUT 0 // outside a word

// count lines, words, and characters in input
int main()
{
    int nl, nw, nc, state;
    nl = nw = nc = 0;
    state = OUT;
    char c;
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

    return 0;
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
