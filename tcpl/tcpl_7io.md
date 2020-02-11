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

p174