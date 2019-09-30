// Exercise7.52.cpp
// Ad
// Using our first version of Sales_data, explain the following initialization.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

int main(int argc, char* argv[])
{
    Sales_data item = {"978", 25, 15.99};
    cout << item.bookNo << ' ' << item.units_sold << ' ' << item.revenue << endl;

    // pause
    cin.get();
    return 0;
}