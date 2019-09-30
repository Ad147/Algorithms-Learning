// Exercise8.07.cpp
// Ad
// Revise the bookstore program from the previous section to write its output to a file.
// Pass the name of the file as a second argument to main.

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
    std::ofstream out(argv[2]);
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
                out << total.bookNum << std::endl
                    << total.numSold << std::endl
                    << total.revenue << std::endl;
                total = tran;
            }
        }
        out << total.bookNum << std::endl
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