CppPrimerCh1.md

C++ Primer Notes
================================================================================

Ad  
init: Apr17.2018  

Chapter1 Getting Started
--------------------------------------------------------------------------------

### 1.1

`int main() {return 0;}`

#### 1.1.1

Command to run compiler:  
`$ g++ -o program1.cpp` (GNU),  
`C:\path\ cl /EHse program1.cpp` (MSVS)

### 1.2

`#include <iostream>` `std::cout <<` `std::endl` `std::cin >>`

### 1.3

`//  Comment` `/* Comment */`

#### 1.4.1

`while (condition) {statement}`  
`++i` & `i++`

#### 1.4.2

`for (init-statement; condition; expression) {}`

#### 1.4.3

Reading an unknown number of inputs

```cpp
while (std::cin >> value)
```

input end-of-file: `control-z` (Win), `control-d` (Mac)

#### 1.4.4

`if () {} else {}`  
`=` & `==`

#### 1.5.1

class with operators: `>>` `<<` `=` `+` `+=`

#### 1.5.2

Member function: dot operator `.`, call operator `()`  
`std::cerr`

### 1.6

The bookstore program

--------------------------------------------------------------------------------

EOF
