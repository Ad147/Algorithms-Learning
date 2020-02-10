tcpl_7io.md

TCPL Notes: 7 Input & Output
================================================================================

A~0b10

--------------------------------------------------------------------------------

- [7.1 Standard Input & Output](#71-standard-input--output)
- [7.2 Formatted Output -- Printf](#72-formatted-output----printf)
- [7.3 Variable-length Argument Lists](#73-variable-length-argument-lists)

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

p169