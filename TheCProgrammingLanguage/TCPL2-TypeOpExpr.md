TCPL2-TypeOpExpr.md

Notes of The C Programming Language
================================================================================

Ad

Init: 191010

Chapter 2: Types, Operators, and Expressions
--------------------------------------------------------------------------------

- [2.1 Variable Names](#21-variable-names)
- [2.2 Data Types and Sizes](#22-data-types-and-sizes)
- [2.3 Constants](#23-constants)
- [2.4 Declarations](#24-declarations)
- [2.5 Arithmetic Operators](#25-arithmetic-operators)
- [2.6 Relational and Logical Operators](#26-relational-and-logical-operators)
- [2.7 Type Conversions](#27-type-conversions)
- [2.8 Increment and Decrement Operators](#28-increment-and-decrement-operators)

--------------------------------------------------------------------------------

### 2.1 Variable Names

Traditional C practice: lower case for variable name; all upper case for symbolic constants.

--------------------------------------------------------------------------------

### 2.2 Data Types and Sizes

Basic types:

- `char`: single byte
- `int`: reflect the natural size of integers on the host machine
- `float`: single-precision floating point
- `double`: double-precision
- Qualilfiers:
  - `short (int)`
  - `long (int)/double`
  - `unsigned char/integer`
  - `signed`

--------------------------------------------------------------------------------

### 2.3 Constants

Suffix:

- `123l` / `123L`
- `123u` / `123U`
- `1.2f` / `1.2F` (default is double)
- `1.2l` / `1.2L`: long double
- `0123`: octal
- `0x12` / `0X12`: hexadecimal
- `'\ooo'`(ooo is 1 to 3 octal digits) = 0ooo
- `'\xhh'`(hh is 1+ hex digits) = 0xhh

###### Complete set of escape sequences

|      |                        |        |                    |
| ---- | ---------------------- | ------ | ------------------ |
| `\a` | alert (bell) character | `\\`   | backslash          |
| `\b` | backspace              | `\?`   | question mark      |
| `\f` | formfeed               | `\'`   | single quote       |
| `\n` | newline                | `\"`   | double quote       |
| `\r` | carriage return        | `\ooo` | octal number       |
| `\t` | horizontal tab         | `\xhh` | hexadecimal number |
| `\v` | vertical tab           |

```cs
/* strlen: return length of s */
int strlen(char s[])
{
    int i;

    i = 0;
    while (s[i] != `\0`)
        ++i;
    return i;
}
```

**Enumeration constant**: `enum boolean { NO = 0, YES };`  
Names in different enumerations must be distinct; Values need not be distinct in the same enumeration.

--------------------------------------------------------------------------------

### 2.4 Declarations

```cs
int lower, upper, step;
int limit = MAXLINE + 1;
const char msg[] = "warning: ";
int strlen(const char[]);
```

--------------------------------------------------------------------------------

### 2.5 Arithmetic Operators

`+`, `-`, `*`, `/`, `%`

--------------------------------------------------------------------------------

### 2.6 Relational and Logical Operators

`>`, `>=`, `<`, `<=`, `==`, `!=`, `&&`, `||`

--------------------------------------------------------------------------------

### 2.7 Type Conversions

```cs
/* atoi: convert s to integer */
int atoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
```

```cs
/* lower : convert c to lower case; ASCII only */
int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}
```

**cast** operator (forced conversion): `(type-name) experssion`

```cs
unsigned long int next = 1;

/* rand: return pseudo-random integer on 0..32767 */
int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

/* srand: set seed for rand() */
void srand(unsigned int seed)
{
    next = seed;
}
```

--------------------------------------------------------------------------------

### 2.8 Increment and Decrement Operators

