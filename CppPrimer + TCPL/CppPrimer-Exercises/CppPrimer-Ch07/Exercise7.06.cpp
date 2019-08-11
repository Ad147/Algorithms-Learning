// Exercise7.06.cpp
// Ad
// Define your own versions of the add, read and print functions.

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

// auxiliary functions
SaleData add(const SaleData &data1, const SaleData &data2);
std::ostream &print(std::ostream &os, const SaleData &data);
std::istream &read(std::istream &is, SaleData &data);

int main(int argc, char* argv[])
{

    // pause
    system("pause");
    return 0;
}

// member function definitions
SaleData &SaleData::combine(const SaleData &data1)
{
    numSold += data1.numSold;
    revenue += data1.revenue;
    return *this;
}

SaleData add(const SaleData &data1, const SaleData &data2)
{
    SaleData sum{data1};
    sum.combine(data2);
    return sum;
}

std::ostream &print(std::ostream &os, const SaleData &data)
{
    os << "ISBN: " << data.isbn() << endl
       << "Sold: " << data.numSold << endl
       << "Revenue: " << data.revenue << endl;
    return os;
}

std::istream &read(std::istream &is, SaleData &data)
{
    is >> data.bookNum >> data.numSold >> data.revenue;
    return is;
}