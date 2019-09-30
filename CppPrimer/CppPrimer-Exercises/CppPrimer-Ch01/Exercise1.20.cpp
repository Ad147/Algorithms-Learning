//  Exercise1.20.cpp
//  Ad
//  Write a program that reads a set of book sales transactions, writing each transaction to the standard output.

#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item book;
    while (std::cin >> book)
    {
        std::cout << book <<std::endl;
    }
    
    //  Pause
    system("pause");
    return 0;
}