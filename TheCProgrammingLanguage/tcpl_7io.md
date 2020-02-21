tcpl_7io.md

TCPL Notes: 7 Input & Output
================================================================================

A~0b10

--------------------------------------------------------------------------------

- [7.1 Standard Input & Output](#71-standard-input--output)
- [7.2 Formatted Output -- Printf](#72-formatted-output----printf)
- [7.3 Variable-length Argument Lists](#73-variable-length-argument-lists)
- [7.4 Formatted Input -- Scanf](#74-formatted-input----scanf)
- [7.5 File Access](#75-file-access)
- [7.6 Error Handling -- Stderr and Exit](#76-error-handling----stderr-and-exit)
- [7.7 Line Input and Output](#77-line-input-and-output)
- [7.8 Miscellaneous Functions](#78-miscellaneous-functions)
  - [7.8.1 String Operations](#781-string-operations)
  - [7.8.2 Character Class Testing and Conversion](#782-character-class-testing-and-conversion)
  - [7.8.3 Ungetc](#783-ungetc)
  - [7.8.4 Command Execution](#784-command-execution)
  - [7.8.5 Storage Management](#785-storage-management)
  - [7.8.6 Mathematical Functions](#786-mathematical-functions)
  - [7.8.7 Random Number Generation](#787-random-number-generation)

7.1 Standard Input & Output
--------------------------------------------------------------------------------

- `int getchar(void)`: read 1 char and returns
- `prog <infile`(cmdln): getchar in prog redirected to infile
- `otherprog | prog`(cmdln): program piping, std output of otherprog into std input of prog
- `int putchar(int)`: std output
- `prog >outfile`: redirect output

>  As we mentioned earlier, "functions" like `getchar` and `putchar` in `<stdio.h>` and `tolower` in `<ctype.h>` are often macros, thus avoiding the overhead of a function call per character. We will show how this is done in Section 8.

7.2 Formatted Output -- Printf
--------------------------------------------------------------------------------

`int printf(char *format, arg1, arg2, ...)`: returns the number of chars printed.

For `%-1.2hc`:

- `-`: left adjustment
- `1`: min field width
- `2`: precision, max number of characters to be printed from a string, or the number after decimal point
- `h`: (or l) printed as a short/long

###### Table 7.1 Basic Printf Conversions

| Character | Argument Type | Printed as                                                                                       |
| --------- | ------------- | ------------------------------------------------------------------------------------------------ |
| d, i      | int           | decimal number                                                                                   |
| o         | int           | unsigned octal number (without a leading zero)                                                   |
| x, X      | int           | unsigned hexadecimal number (without a leading 0x or 0X), using abcdef or ABCDEF for 10, ..., 15 |
| u         | int           | unsigned decial number                                                                           |
| c         | int           | single character                                                                                 |
| s         | char *        | print characters from the string until a '\0' or the number of characters given by the precision |
| f         | double        | default 6 precision                                                                              |
| e, E      | double        | scientific notation                                                                              |
| g, G      | double        | use %e/E if (exp < -4 or >= precision), otherwise %f                                             |
| p         | void *        | pointer (implementation-dependent representation)                                                |
| %         |               | '%'                                                                                              |

`printf("%.*s", max, s);`: a width/precision may be specified as *, indicatingthe value is computed by converting the next argument.

`int sprintf(char *str, char *format, arg1, arg2, ...)` does the same conversions as printf, but stores the output in a string.

7.3 Variable-length Argument Lists
--------------------------------------------------------------------------------

```cxx
#include <stdarg.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;     /* points to each unnnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);  /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);     /* clean up when done */
}
```

7.4 Formatted Input -- Scanf
--------------------------------------------------------------------------------

`int scanf(char *format, ...)`

`int sscanf(char *string, char *format, ptr1, ptr2, ...)`

###### Table 7.2 Basic Scanf Conversions

| Character | Input Data                                                      | Argument Type                    |
| --------- | --------------------------------------------------------------- | -------------------------------- |
| d         | decimal integer                                                 | int *                            |
| i         | integer (may be octal (0-) or hexadeciaml (ox/X-))              | int *                            |
| o         | octal int(with/without 0)                                       | int *                            |
| u         | unsigned decimal                                                | unsigned int *                   |
| x         | hexadecimal (with/without 0x)                                   | int *                            |
| c         | characters                                                      | char *                           |
| s         | character string (not quoted)                                   | char *, to an array large enough |
| e, f, g   | floating-point number with optional sign/decimal point/exponent | float *                          |
| %         | literal %                                                       | no assignment is made            |

```cxx
#include <stdio.h>

main()  /* rudimentary calculator */
{
    double sum, v;

    sum = 0;
    while (scanf("%lf", &v) == 1)
        printf("\t%.2f\n", sum += v);
    return 0;
}
```

> scanf ignores blanks and tabs in its format string.  
> Furthermore, it skips over white space (blanks, tabs, newlines, etc.) as it looks for input values.  
> To read input whose format is not fixed, it is often best to read a line at a time, then pick it apart with sscanf.

```cxx
while (getline(line, sizeof(line)) > 0) {
    if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
        printf("valid: %s\n", line);    /* 25 Dec 1988 form */
    else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
        printf("valid: %s\n", line);    /* mm/dd/yy form */
    else
        printf("invalid: %s\n", line);  /* invalid form */
}
```

7.5 File Access
--------------------------------------------------------------------------------

```cxx
FILE *fp;
FILE *fopen(char *name, char *mode);
/* FILE is a type name defined by typedef, not a structure tag */

fp = fopen(name, mode);
/* modes: r, w, a (append), and b for binary files */

int getc(FILE *fp);
int putc(int c, FILE *fp);
/* getc and putc may be macros instead */

int fscanf(FILE *fp, char *format, ...)
int fprintf(FILE *fp, char *format, ...)
```

```cxx
#include <stdio.h>

/* cat: concatenate files, version 1 */
main(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);

    if (argc == 1)  /* no args; copy standard input */
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("cat: cannot open %s\n", *argv);
                return 1;
            } else {
                filecopy(fp, stdout);
                fcloste(fp);
            }
    return 0;
}

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}
```

7.6 Error Handling -- Stderr and Exit
--------------------------------------------------------------------------------

```cxx
#include <stdio.h>

/* cat: concatenate files, version 2 */
main(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0];   /* program name for errors */

    if (argc == 1)      /* no args; copy std input */
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp == fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: cannot open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}
```

The program uses standard library function exit, which terminates program execution.  
The argument of exit is available to whatever process called this one.  
exit calls fclose for each open output file, to flush out any buffered output.

Within main, `return expr` is equivalent to `exit(expr)`.  
exit can be called from other functions.

`int ferror(FILE *fp)` and `int feof(FILE *fp)` returns non-zero if an error/end of file occurred on the stream fp.

7.7 Line Input and Output
--------------------------------------------------------------------------------

```cxx
/* fgets: get at most n chars from iop */
char *fgets(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)
        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

/* fputs: put string s on file iop */
int fputs(char *s, FILE *iop)
{
    int c;

    while (c == *s++)
        putc(c, iop);
    return ferror(iop) ? EOF : 0;
}

/* getline: read a line, return length */
int getline(char *line, int max)
{
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}
```

7.8 Miscellaneous Functions
--------------------------------------------------------------------------------

### 7.8.1 String Operations

| `<string.h>`     |                                                    |
| ---------------- | -------------------------------------------------- |
| strcat(s, t)     | concatenate t to end of s                          |
| strncat(s, t, n) | concatenate n characters of t to end of s          |
| strcmp(s, t)     | return negative, zero, or positive for s </==/> t  |
| strncmp(s, t, n) | compare first n chars                              |
| strcpy(s, t)     | copy t to s                                        |
| strncpy(s, t, n) | copy at most n characters                          |
| strlen(s)        | return length of s                                 |
| strchr(s, c)     | return ptr to first c in s, or NULL if not present |
| strrchr(s, c)    | return ptr to last c in s, or NULL if not present  |

### 7.8.2 Character Class Testing and Conversion

| `<ctype.h>` |                                                     |
| ----------- | --------------------------------------------------- |
| isalpha(c)  | non-zero if c is alphabetic, 0 if not               |
| isupper(c)  | ~                                                   |
| islower(c)  | ~                                                   |
| isdigit(c)  | ~                                                   |
| isalnum(c)  | ~                                                   |
| isspace(c)  | blank, tab, newline, return, formfeed, vertical tab |
| toupper(c)  | return c converted to upper case                    |
| tolower(c)  | return c converted to lower case                    |

### 7.8.3 Ungetc

`int ungetc(int c, FILE *fp)`

### 7.8.4 Command Execution

`system(char *s)`

### 7.8.5 Storage Management

`void *malloc(size_t n)`

returns a ptr to n bytes of uninitialized storage, or NULL.

`void *calloc(size_t n, size_t size)`

returns a ptr to enough space for an array of n objs of the specified size, or NULL.  
The storage is initialized to zero.

The ptr must be cast into the appropriate type: `int *ip; ip = (int *) calloc(n, sizeof(int));`

`free(p)`

frees the space obtained by a call to malloc or calloc.

### 7.8.6 Mathematical Functions

| `<math.h>`  |                                         |
| ----------- | --------------------------------------- |
| sin(x)      | sine of x, x in radians                 |
| cos(x)      | cosine                                  |
| atan2(y, x) | arctangent of y/x, in radians           |
| exp(x)      | exponential function e^x                |
| log(x)      | natural (base e) logarithm of x (x > 0) |
| log10(x)    | common (base 10) logarithm of x (x > 0) |
| pow(x, y)   | x^y                                     |
| sqrt(x)     | square root of x (x >= 0)               |
| fabs(x)     | absolute value of x                     |

### 7.8.7 Random Number Generation

`rand()` (stdlib): a sequence of pseudo-random integers in 0 to RAND_MAX.

One way to produce random floating-point numbers (0 <= f <1):

`#define frand() ((double) rand() / (RAND_MAX+1.0))`

`srand(unsigned)` sets to seed for rand.

--------------------------------------------------------------------------------

EOF
