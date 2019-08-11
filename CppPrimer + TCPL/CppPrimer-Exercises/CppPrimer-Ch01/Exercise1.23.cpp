//  Exercise1.23.cpp
//  Ad
//  Write a program that reads several transactions and counts how many transactions occur for each ISBN.

#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item currentItem, item;
    if (std::cin >> currentItem)
    {
        int cnt = 1;
        while (std::cin >> item)
        {
            if (item.isbn() == currentItem.isbn())
            {
                ++cnt;
            }
            else 
            {
                std::cout << "ISBN: " << currentItem.isbn() << " occurs " << cnt << " time(s)" << std::endl;
                currentItem = item;
                cnt = 1;
            }
        }
        std::cout << "ISBN: " << currentItem.isbn() << " occurs " << cnt << " time(s)" << std::endl;
    }

    //  Pause
    system("pause");
    return 0;
}