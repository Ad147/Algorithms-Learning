// Exercise8.08.cpp
// Ad
// Revise the program from the previous exercise to append its output to its given file.
// Run the program from the same output file at least twice to ensure that the data are preserved.

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
    std::ofstream out(argv[2], std::ofstream::app);
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