CppPrimerCh01.md

C++ Primer Notes
================================================================================

Ad  
init: Apr17.2018  

Chapter1 Getting Started
--------------------------------------------------------------------------------

### 1.1 Writing a Simple C++ Program

```cpp
int main()
{
    return 0;
}
```

#### 1.1.1 Compliling and Executing Our Program

Command to run compiler:  
`$ g++ -o program1.cpp` (GNU),  
`C:\path\ cl /EHse program1.cpp` (MSVS)

### 1.2 A First Look at Input/Output

`#include <iostream>`  
`std::cout <<`  
`std::endl`  
`std::cin >>`

### 1.3 A word about Comments

`//  Comment`  
`/* Comment */`

### 1.4 Flow of Control

#### 1.4.1 The `while` Statement

```cpp
while (condition)
    statement
```

`++i` & `i++`

#### 1.4.2 The `for` Statement

`for (init-statement; condition; expression)`

#### 1.4.3 Reading an Unknown Number of Inputs

```cpp
while (std::cin >> value)
{
    // do something
}
```

input end-of-file: `control-z` (Win), `control-d` (Mac)

#### 1.4.4 The `if` Statement

```cpp
if (condition)
    statement1
else
    statement2
```

`=` & `==`

### 1.5 Introducing Classes

#### 1.5.1 The `Sales_item` Class

#### 1.5.2 A First Look at Member Functions

Member function: dot operator `.`, call operator `()`  
`std::cerr`

### 1.6 The Bookstore Program

###### The bookstore program

```cpp
#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item total; // variable to hold data for the next transaction
    // read the first transaction and ensure that there are data to process
    if (std::cin >> total)
    {
        Sales_item trans; // variable to hold the running sum
        // read and process the remaining transactions
        while (std::cin >> trans)
        {
            // if we're still processing the same book
            if (total.isbn() == trans.isbn())
            total += trans; // update the running total
            else
            {
                // print results for the previous book
                std::cout << total << std::endl;
                total = trans;  // total now refers to the next book
            }
        }
    std::cout << total << std::endl; // print the last transaction
    }
    else
    {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
    return 0;
}
```

--------------------------------------------------------------------------------

EOF
