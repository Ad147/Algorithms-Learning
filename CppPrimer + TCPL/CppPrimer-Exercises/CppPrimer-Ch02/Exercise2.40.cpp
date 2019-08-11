//  Exercise2.40.cpp
//  Ad
//  Write your own version of the Sales_data class.

#include <iostream>
#include <string>

struct SaleDate
{
    std::string bookNumber;
    int unitSold{0};
    double revenue{0};
};

int main()
{
    SaleDate data1{"123", 1, 7};
    std::cout << data1.bookNumber << '\t' << data1.unitSold << '\t' << data1.revenue << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}