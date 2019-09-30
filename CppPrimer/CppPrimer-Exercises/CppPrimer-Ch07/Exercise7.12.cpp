// Exercise7.12.cpp
// Ad
// Move the definition of the SaleData constructor that takes an istream into
// the body og the class.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

// class declaration -----------------------------------------------------------

struct SaleData
{
    // constructors
    SaleData() = default;
    SaleData(const std::string &s) : bookNum(s) { }
    SaleData(const std::string &s, unsigned n, double d) :
             bookNum(s), numSold(n), revenue(d) { }
    SaleData(std::istream &is) { is >> bookNum >> numSold >> revenue; }

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

// main ------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    SaleData t1;
    SaleData t2("T2");
    SaleData t3("T3", 1, 2);
    print(cout, t1);
    print(cout, t2);
    print(cout, t3);

    //  pause
    system("pause");
    return 0;
}

// member functions ------------------------------------------------------------

SaleData &SaleData::combine(const SaleData &data1)
{
    // code to debug
    std::cerr << ">>> Function called: [" << __func__ << "] <<<" << endl;
    numSold += data1.numSold;
    revenue += data1.revenue;
    return *this;
}

SaleData add(const SaleData &data1, const SaleData &data2)
{
    std::cerr << ">>> Function called: [" << __func__ << "] <<<" << endl;
    SaleData sum{data1};
    sum.combine(data2);
    return sum;
}

std::ostream &print(std::ostream &os, const SaleData &data)
{
    std::cerr << ">>> Function called: [" << __func__ << "] <<<" << endl;
    os << "ISBN: " << data.isbn() << endl
       << "Sold: " << data.numSold << endl
       << "Revenue: " << data.revenue << endl;
    return os;
}

std::istream &read(std::istream &is, SaleData &data)
{
    std::cerr << ">>> Function called: [" << __func__ << "] <<<" << endl;
    is >> data.bookNum >> data.numSold >> data.revenue;
    return is;
}