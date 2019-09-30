// Exercise7.02.cpp
// Ad
// Add the combine and isbn members to the Sales_data class you wrote.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;


struct SaleData
{
    // member functions
    std::string isbn() const { return bookNum; }
    SaleData &combine(const SaleData &data1);

    // member variables
    std::string bookNum;
    unsigned numSold;
    double revenue;
};

int main(int argc, char* argv[])
{

    // pause
    system("pause");
    return 0;
}

// member function definitions
SaleData &SaleData::combine(const SaleData &data1);
{
    numSold += data1.numSold;
    revenue += data1.revenue;
    return *this;
}