// Exercise11.11.cpp
// Ad
// Redefine bookstore without using decltype.

#include <iostream>
#include <string>
#include <set>

// class -----------------------------------------------------------------------

class Sales_data
{
  public:
    Sales_data(std::string s) : booknum(s) {}

    std::string isbn() const { return booknum; }

  private:
    std::string booknum;
};

// function --------------------------------------------------------------------

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::multiset<Sales_data,
                  bool (*)(const Sales_data &lhs, const Sales_data &rhs)>
        bookstore(compareIsbn);

    // pause
    system("pause");
    return 0;
}