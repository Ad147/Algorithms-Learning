// Exercise7.03.cpp
// Ad
// Revise your transaction-processing program to use these members.

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
    SaleData total;
    if (cin >> total.bookNum >> total.numSold >> total.revenue)
    {
        SaleData tran;
        while (cin >> tran.bookNum >> tran.numSold >> tran.revenue)
        {
            if (tran.isbn() == total.isbn())
            {
                total.combine(tran);
            }
            else
            {
                cout << total.bookNum << endl
                     << total.numSold << endl
                     << total.revenue << endl;
                total = tran;
            }
        }
        cout << total.bookNum << endl
             << total.numSold << endl
             << total.revenue << endl;
    }
    else
    {
        std::cerr << "No data." << endl;
        return -1;
    }

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