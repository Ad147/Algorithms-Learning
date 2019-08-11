// Exercise8.06.cpp
// Ad
// Rewrite the bookstore program from p.256 to read its transactions from a file.
// Pass the name of the file as an argument to main.

#include <iostream>
#include <fstream>
#include <string>

// class -----------------------------------------------------------------------

struct SaleData
{
    std::string bookNum;
    unsigned numSold;
    double revenue;
};

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::ifstream in(argv[1]);
    SaleData total;
    if (in >> total.bookNum >> total.numSold >> total.revenue)
    {
        SaleData tran;
        while (in >> tran.bookNum >> tran.numSold >> tran.revenue)
        {
            if (tran.bookNum == total.bookNum)
            {
                total.numSold += tran.numSold;
                total.revenue += tran.revenue;
            }
            else
            {
                std::cout << total.bookNum << std::endl
                          << total.numSold << std::endl
                          << total.revenue << std::endl;
                total = tran;
            }
        }
        std::cout << total.bookNum << std::endl
                  << total.numSold << std::endl
                  << total.revenue << std::endl;
    }
    else
    {
        std::cerr << "No data." << std::endl;
        return -1;
    }

    // pause
    system("pause");
    return 0;
}