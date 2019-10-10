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

--------------------------------------------------------------------------------

### 2.1 Variable Names

Traditional C practice: lower case for variable name; all upper case for symbolic constants.

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

|      |     |     |     |
| ---- | --- | --- | --- |
| `\a` |