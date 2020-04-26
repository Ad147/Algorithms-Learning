tcpl_Bstdlib.md

TCPL Appendix B Standard Library
================================================================================

A~0d10

--------------------------------------------------------------------------------

- [B1 Input and Output: <stdio.h>](#b1-input-and-output-stdioh)
  - [B1.1 File Operations](#b11-file-operations)
  - [B1.2 Formatted Output](#b12-formatted-output)
  - [B1.3 Formatted Input](#b13-formatted-input)
  - [B1.4 Character Input and Output Functions](#b14-character-input-and-output-functions)
  - [B1.5 Direct Input and Output Functions](#b15-direct-input-and-output-functions)
  - [B1.6 File Positioning Functions](#b16-file-positioning-functions)
  - [B1.7 Error Functions](#b17-error-functions)
- [B2 Character Class Tests: <ctype.h>](#b2-character-class-tests-ctypeh)
- [B3 String Functions: <string.h>](#b3-string-functions-stringh)
- [B4 Mathematical Functions: <math.h>](#b4-mathematical-functions-mathh)
- [B5 Utility Functions: <stdlib.h>](#b5-utility-functions-stdlibh)
- [B6 Diagnostics: <assert.h>](#b6-diagnostics-asserth)
- [B7 Variable Argument Lists: <stdarg.h>](#b7-variable-argument-lists-stdargh)
- [B8 Non-local Jumps: <setjmp.h>](#b8-non-local-jumps-setjmph)
- [B9 Signals: <signal.h>](#b9-signals-signalh)
- [B10 Date and Time Functions: <time.h>](#b10-date-and-time-functions-timeh)
- [B11 Implementation-defined Limits: <limits.h> and <float.h>](#b11-implementation-defined-limits-limitsh-and-floath)

Headers:

|            |            |            |            |            |
| ---------- | ---------- | ---------- | ---------- | ---------- |
| <assert.h> | <float.h>  | <math.h>   | <stdarg.h> | <stdlib.h> |
| <ctype.h>  | <limits.h> | <setjmp.h> | <stddef.h> | <string.h> |
| <errno.h>  | <locale.h> | <signal.h> | <stdio.h>  | <time.h>   |

B1 Input and Output: <stdio.h>
--------------------------------------------------------------------------------

### B1.1 File Operations

```cxx
FILE *fopen(const char *filename, const char *mode)

FILE *freopen(const char *filename, const char *mode, FILE *stream)

int fflush(FILE *stream)

int fclose(FILE *stream)

int remove(const char *filename)

int rename(const char *oldname, const char *newname)

FILE *tmpfile(void)

char *tmpnam(char s[L_tmpnam])

int setvbuf(FILE *stream, char *buf, int mode, size_t size)

int setbuf(FILE *stream, char *buf)
```

### B1.2 Formatted Output

```cxx
int fprintf(FILE *stream, const char *format, ...)
```

returns the number of chars written, or negative if error.

...

```cxx
int printf(const char *format, ...)
// == fprintf(stdout,...)

int sprintf(char *s, const char *format, ...)
// same as printf except that output is into s

vprintf(const char *format, va_list arg)
vfprintf(FILE *stream, const char *format, va_list arg)
vsprintf(char *s, const char *format, va_list arg)
// equivalent to corresponding printf functions, except that variable argument list is replaced by `arg`
// <stdarg.h> see B7
```

### B1.3 Formatted Input

```cxx
int fscanf(FILE *stream, const char *format, ...)

int scanf(const char *format, ...)
// == fscsnf(stdin,...)

int sscanf(char *s, const char *format, ...)
// == scanf(...) except that the input are from s
```

### B1.4 Character Input and Output Functions

```cxx
int fgetc(FILE *stream)

char *fgets(char *s, int n, FILE *stream)

int fputc(int c, FILE *stream)

int fputs(const char *s, FILE *stream)

int getc(FILE *stream)
// == fgetc except that if it is a macro, it may evaluate stream > once

int getchar(void)
// == getc(stdin)

char *gets(char *s)

int putc(int c, FILE *stream)
// == fputc except that if it is a macro, it may evaluate stream > once

int putchar(int c)
// == putc(c, stdout)

int puts(const char *s)

int ungetc(int c, FILE *stream)
```

### B1.5 Direct Input and Output Functions

```cxx
size_t fread(void *ptr, size_t size, size_t nobj, FILE *stream)

size_t fwrite(const void *ptr, size_t size, size_t nobj, FILE *stream)
```

### B1.6 File Positioning Functions

```cxx
int fseek(FILE *stream, long offset, int origiin)

long ftell(FILE *stream)

void rewind(FILE *stream)

int fgetpos(FILE *stream, fpos_t *ptr)

int fsetpos(FILE *stream, const fpos_t *ptr)
```

### B1.7 Error Functions

Many of the functions int the library set status indicators when error or EOF occur.  
These indicators may be set and tested explicitly.

```cxx
void clearerr(FILE *stream)

int feof(FILE *stream)

int ferror(FILE *stream)

void perror(const char *s)
```

B2 Character Class Tests: <ctype.h>
--------------------------------------------------------------------------------

Functions for testing characters.  
For each function, the arg is an int, whose value is EOF or representable as an unsigned char.  
Returns an int,  
non-zero if arg satisfies the condition, zero if not.

```cxx
isupper(c)  /* upper-case letter */
islower(c)  /* lower-case letter */
isalpha(c)  /* isupper(c) or islower(c) is true */
isdigit(c)  /* decimal digit */
isxdigit(c) /* hexadecimal digit */
isalnum(c)  /* isalpha(c) or isdigit(c) is true */
isspace(c)  /* space, formfeed, newline, carriage return, tab, vertical tab */
ispunct(c)  /* printing character except space or letter or digit */
isgraph(c)  /* printing character except space */
isprint(c)  /* printing character including space */
iscntrl(c)  /* control character */
```

In 7-bit ASCII character set,

- printing characters: 0x20(' ') to 0x7E('~')
- control characters: 0(NUL) to 0x1F(US), and 0x7F(DEL)

Converting case functions:

```cxx
int tolower(int c)
int toupper(int c)
```

B3 String Functions: <string.h>
--------------------------------------------------------------------------------

Comparison functions treat arguments as unsigned char arrays.

In following,

- `s` and `t`: `char *`
- `cs` and `ct`: `const char *`
- `n`: `size_t`
- `c`: an `int` converted to `char`.

```cxx
char *strcpy(s, ct)         /* copy ct to s, including '\0'; return s. */

char *strncpy(s, ct, n)     /* copy at most n chars of ct to s; return s. Pad with '\0's if t has < n */

char *strcat(s, ct)         /* concatenate ct to end of s; return s */

char *strncat(s, ct, n)     /* concatenate at most n of  ct to end of s; return s */

int strcmp(cs, ct)          /* compare cs to ct; return <0/0/>0 if cs</==/>ct */

int strncmp(cs, ct, n)      /* compare at most n chars */

char *strchr(cs, c)         /* return ptr to 1st occurrence of c in cs or NULL */

char *strrchr(cs, c)        /* return ptr to last occurrence of c in cs or NULL */

size_t strspn(cs, ct)       /* return length of prefix of cs consisting of chars in ct */

size_t strcspn(cs, ct)      /* return length of prefix of cs consisting of chars not in ct */

char *strpbrk(cs, ct)       /* return ptr to 1st occurrence in cs of any char of ct, or NULL */

char *strstr(cs, ct)        /* return ptr to 1st occurrence of ct in cs, or NULL */

size_t strlen(cs)           /* return length of cs */

char *strerror(n)           /* return ptr to implementation-defined string corresponding to error n */

char *strtok(s, ct)         /* strtok searchs s for tokens delimited by chars from ct; see below */
```

The mem... functions are meant for manipulating objects as character arrays.

- `s` and `t`: `void *`
- `cs` and `ct`: `const void *`
- `n`: `size_t`
- `c`: an `int` converted to an `unsigned char`

```cxx
void *memcpy(s, ct, n)      /* copy n chars from ct to s, return s */

void *memmove(s, ct, n)     /* same as memcpy except that it works even if the obje overlap. */

int memcmp(cs, ct, n)       /* compare the first n chars of cs with ct; return as with strcmp. */

void *memchr(cs, c, n)      /* return ptr to first occurrence of char c in cs, or NULL if not present among first n chars. */

void *memset(s, c, n)       /* place character c into first n chars of s return s. */
```

B4 Mathematical Functions: <math.h>
--------------------------------------------------------------------------------

The macros EDOM and ERANGE (found in <errno.h>) are used to signal domain and range errors.  
Domain error: argument outside the domain over which the function is defined;  
Range error: result overflows or underflows.

- `x` and `y`: `double`
- `n`: `int`
- all functions return `double`
- angles for trigonometric are expressed in radians

```cxx
sin(x)
cos(x)
tan(x)
asin(x)
acos(x)
atan(x)
atan2(y, x)     /* tan^-1(y/x) */
sinh(x)         /* hyperbolic sine of x */
cosh(x)
tanh(x)
exp(x)
log(x)
log10(x)
pow(x, y)
sqrt(x)
ceil(x)
floor(x)
fabs(x)         /* absolute value |x| */
ldexp(x, n)     /* x * 2^n */
frexp(x, int *exp)  /* ... */
modf(x, double *ip) /* ... */
fmod(x, y)      /* floating-point remainder of x/y, with the same sign as x. */
```

B5 Utility Functions: <stdlib.h>
--------------------------------------------------------------------------------

Functions for number conversion, storage allocation, and similar tasks.

```cxx
double atof(const char *s)      /* convert s to double; == strtod(s, (char**)NULL) */

int atoi(const char *s)         /* convert s to int; == strtol(s, (char**)NULL, 10) */

long atol(const char *s)        /* convert s to long; == strtol(s, (char**)NULL, 10) */

double strtod(const char *s, char **endp)   /* convert prefix of s to double, ignoring leading space; it stores a ptr to any unconverted suffix in *endp unless NULL */

long strtol(const char *s, char **endp, int base)   /* convert prefix of s to long, ignoring leading space; it stores a ptr to any unconverted suffix in *endp unless NULL. if base is [2, 36], it assume the input in that base. if base is 0, the base is 8(leading 0), 10, or 16(leading 0x).letters represent digits from 10 to base-1. */

unsigned long strtoul(const char *s, char **endp, int base)

int rand(void)              /* return pseudo-random integer in 0~RAND_MAX, which is at least 32767. */

void srand(unsigned int seed)   /* use seed for a new sequence of pseudo-random numbers, initial seed is 1. */

void *calloc(size_t nobj, size_t size)  /* return a ptr to space for an array of nobj objects, each of size size, the space initialized to 0 bytes. */

void *malloc(size_t size)   /* return a ptr to space for an object of size size, the space is uninitialized. */

void *realloc(void *p, size_t size)     /* change size of the object pointed by p to size. the content will be unchanged up to the minimum of the old and new sizes. if new is larger, the new space is uninitialized. */

void free(void *p)          /* deallocate the space pointed to by p; p must be previously allocated by calloc, malloc, or realloc. */

void abort(void)            /* cause the program to terminate abnormally, as if by raise(SIGABRT). */

void exit(int status)       /* cause normal termination. atexit functions are called in reverse order of registration, open files are flushed, open streams are closed, and control is returned to the environment. status is implementation-dependent, but 0 is successful termination. */

int atexit(void (*fcn)(void))

int system(const char *s)   /* passes the string s to the environment for execution. */

char *getenv(const char *name)

void *bsearch(const void *key, const void *base, size_t n, size_t size, int (*cmp)(const void *keyval, const void *datum))  /* search base[0]...base[n-1] for *key. items in base must be in ascending order. */

void qsort(void *base, size_t n, size_t size, int (*cmp)(const void *, const void *))   /* sort into ascending order an array base of objects of size size. */

int abs(int n)      /* absolute value */
long labs(long n)

div_t div(int num, int denom)   /* computes the quotient and remainder of num/denom. results are stored in the int members quot and rem of a structure of type div_t. */
ldiv_t ldiv(long num, long denom)
```

B6 Diagnostics: <assert.h>
--------------------------------------------------------------------------------

The `assert` macro is used to add diagnostics to programs:

```cxx
void assert(int expression)
```

if expression is 0 when assert() is executed, the assert macro will print on stderr a message, such as  
`Assertion failed: expression, file filename, line nnn`

It then calls abort() to terminate execution. The filename and linenumber come from the preprocessor macros `__FILE__` and `__LINE__`.

If `NDEBUG` is defined at the time <assert.h> is included, the assert macro is ignored.

B7 Variable Argument Lists: <stdarg.h>
--------------------------------------------------------------------------------

Provides facilities for stepping through a list of function arguments of unknown number and type.

B8 Non-local Jumps: <setjmp.h>
--------------------------------------------------------------------------------

Providing a way to avoid the normal function call and return sequence, typically to permit an immediate return from a deeply nested functon call.

B9 Signals: <signal.h>
--------------------------------------------------------------------------------

Providing facilities for handling exceptional conditions that arise during execution, such as an interrupt from an external source or an error in exection.

B10 Date and Time Functions: <time.h>
--------------------------------------------------------------------------------

`clock_t` and `time_t` are arithmetic types representing times.

`struct tm` holds the components of a calendar time:

- int tm_sec: (0, 61)
- int tm_min: (0, 59)
- int tm_hour: (0, 23)
- int tm_mday: day of month (1, 31)
- int tm_mon: (0, 11)
- int tm_year: since 1900
- int tm_wday: days since Sunday (0, 6)
- int tm_yday: days since January 1 (0, 365)
- int tm_isdst: Daylight Saving Time flag, >0 if in effect; ==0 if not; <0 if the info not available.

```cxx
clock_t clock(void)
/* returning the processor time used by the program since beginning of execution, or -1 if unavailable. clock()/CLOCKS_PER_SEC is a time in seconds. */

time_t time(time_t *tp)
/* returning current calendar time or -1 if not available. return value also assigned to *tp. */

double difftime(time_t time2, time_t time1)
/* returning time2 - time1 expressed in seconds. */

time_t mktime(struct tm *tp)
/* converting local time in tp into calendar time in the same representation used by time. */
```

The next 4 functions return pointers to static objects that may be overwritten by other calls.

```cxx
char * asctime(const struct tm *tp)
/* converting time in tp into a string of the form: Sun Jan 3 15:14:13 1988\n\0 */

char *ctime(const time_t *tp)
/* converting tp to local time; == asctime(localtime(tp)) */

struct tm *gmtime(const time_t *tp)
/* converting tp into Coordinated Universal Time (UTC). */

struct tm *localtime(const time_t *tp)
/* converting tp into local time. */

size_t strftime(char *s, size_t smax, const char *fmt, const struct tm *tp)
/* formating date and time information from *tp into s according to fmt (analogous to printf format):
- %a abbreviated weekday
- %A full weekday
- %b abbreviated month
- %B full month
- %c local date and time representation
- %d day of the month (01-31)
- %H hour (00-23)
- %I hour(01-12)
- %j day of the year (001-366)
- %m month (01-12)
- %M minute (00-59)
- %p local equivalent of AM or PM
- %S second (00-61)
- %U week number (Sunday as 1st day of week) (00-53)
- %w weekday (0-6 since Sunday)
- %W week number (Monday as 1st day of week) (00-53)
- %x local date representation
- %X local time representaion
- %y year without century (00-99)
- %Y year with century
- %Z time zone name, if any
- %% %
no more than smax chars are placed into s. return number of chars, or 0 if more than smax were produced. */
```

B11 Implementation-defined Limits: <limits.h> and <float.h>
--------------------------------------------------------------------------------

<limits.h> defines constants for the sizes of integral types.  
The values below are acceptable minimum magnitudes; larger values may be used.

|           |                        |              |
| --------- | ---------------------: | ------------ |
| CHAR_BIT  |                      8 | bits in char |
| CHAR_MAX  | UCHAR_MAX or SCHAR_MAX |
| CHAR_MIN  |         0 or SCHAR_MIN |
| INT_MAX   |                 +32767 |
| INT_MIN   |                 -32767 |
| LONG_MAX  |            +2147483647 |
| LONG_MIN  |            -2147483647 |
| SCHAR_MAX |                   +127 | signed char  |
| SCHAR_MIN |                   -127 |
| SHRT_MAX  |                 +32767 | short        |
| SHRT_MIN  |                 -32767 |
| UCHAR_MAX |                    255 |
| UINT_MAX  |                  65535 |
| ULONG_MAX |             4294967295 |
| USHRT_MAX |                  65535 |

The names below, a subset of <float.h>, are constants related to floating-point arithmetic.  
The values are minimum magnitude.

|              |       |                                             |
| ------------ | ----: | ------------------------------------------- |
| FLT_RADIX    |     2 | radix of exponent representation, eg. 2, 16 |
| FLT_ROUNDS   |       | floating-point rounding mode for addition   |
| FLT_DIG      |     6 | decimal digits of precision                 |
| FLT_EPSILON  |  1e-5 | smallest number x that 1.0 + x != 1.0       |
| FLT_MANT_DIG |       | number of base FLT_RADIX digits in mantissa |
| FLT_MAX      |  1e37 |
| FLT_MAX_EXP  |       | max n that FLT_DADIX^n-1 is representable   |
| FLT_MIN      | 1e-37 | min normalized floating-point number        |
| FLT_MIN_EXP  |       | min n that 10^n is a normalized number      |
| DBL_DIG      |    10 | decimal digits of precision                 |
| DBL_EPSILON  |  1e-9 | smallest number x that 1.0 + x != 1.0       |
| DBL_MANT_DIG |       | number of base FLT_RADIX digits in mantissa |
| DBL_MAX      |  1e37 |
| DBL_MAX_EXP  |
| DBL_MIN      | 1e-37 |
| DBL_MIN_EXP  |

--------------------------------------------------------------------------------

EOF
