// Exercise7.01.cpp
// Ad
// Write a version of the transaction-processing program using the class you
// defined.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;


struct SaleData
{
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
            if (tran.bookNum == total.bookNum)
            {
                total.numSold += tran.numSold;
                total.revenue += tran.revenue;
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