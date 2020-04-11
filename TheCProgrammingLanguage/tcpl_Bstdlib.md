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
```

```cxx
FILE *freopen(const char *filename, const char *mode, FILE *stream)
```

```cxx
int fflush(FILE *stream)
```

```cxx
int fclose(FILE *stream)
```

```cxx
int remove(const char *filename)
```

```cxx
int rename(const char *oldname, const char *newname)
```

```cxx
FILE *tmpfile(void)
```

```cxx
char *tmpnam(char s[L_tmpnam])
```

```cxx
int setvbuf(FILE *stream, char *buf, int mode, size_t size)
```

```cxx
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
