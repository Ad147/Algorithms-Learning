// Exercise7.14.cpp
// Ad
// Write a version of the default constructor that explicitly initializes the
// members to the values we have provided as in-class initializers.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

// class declaration -----------------------------------------------------------

struct SaleData
{
    // constructors
    SaleData() : bookNum("\0"), numSold(0), revenue(0) { }
    SaleData(const std::string &s) : bookNum(s) { }
    SaleData(const std::string &s, unsigned n, double d) : bookNum(s), numSold(n), revenue(d) { }
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
    SaleData total(cin);
    if (cin)
    {
        SaleData tran;
        while (read(cin, tran))
        {
            if (tran.isbn() == total.isbn())
            {
                total.combine(tran);
            }
            else
            {
                print(cout, total);
                total = tran;
            }
        }
        print(cout, total);
    }
    else
    {
        std::cerr << "No data." << endl;
        return -1;
    }

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