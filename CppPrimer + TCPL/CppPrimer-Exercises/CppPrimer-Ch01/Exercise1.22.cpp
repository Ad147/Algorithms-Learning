//  Exercise1.22.cpp
//  Ad
//  Write a program that reads several transactions for the same ISBN. Write the sum of all the transactions that were read.

#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item sum, item;
    while (std::cin >> item)
    {
        sum += item;
    }
    std::cout << sum <<std::endl;
    
    //  Pause
    system("pause");
    return 0;
}