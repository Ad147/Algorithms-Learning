// Exercise7.41.cpp
// Ad
// Rewrite your Sales_data class to use the delegating constructors.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

// class declaration -----------------------------------------------------------

class SaleData
{
  public:
    // constructor
    SaleData() : SaleData(" ", 0, 0) 
    {
        std::cerr << ">>> [ SaleData() ] <<<" << endl;
    }
    SaleData(const std::string &s) : SaleData(s, 0, 0)
    {
        std::cerr << ">>> [ SaleData(string) ] <<<" << endl;
    }
    SaleData(const std::string &s, unsigned n, double d)
        : bookNum(s), numSold(n), revenue(d) 
    {
        std::cerr << ">>> [ SaleData(string, unsigned, double) ] <<<" << endl;
    }
    SaleData(std::istream &is) : SaleData()
    {
        std::cerr << ">>> [ SaleData(istream&) ] <<<" << endl;
        is >> bookNum >> numSold >> revenue;
    }

  private:
    std::string bookNum;
    unsigned numSold;
    double revenue;
};


// main ------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    cout << "data1:" << endl;
    SaleData data1;
    cout << endl << "data2:" << endl;
    SaleData data2("a");
    cout << endl << "data3:" << endl;
    SaleData data3("a", 1, 1);
    cout << endl << "data4:" << endl;
    SaleData data4(cin);

    //  pause
    system("pause");
    return 0;
}