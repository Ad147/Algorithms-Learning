// Exercise11.19.cpp
// Ad
// Define a variable that you initialize by calling  begin() on the multiset named bookstore from page 425.
// Write the variable's type without using auto or decltype.

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

    // write the type without using auto or decltype
    std::multiset<Sales_data,
                  bool (*)(const Sales_data &, const Sales_data &)>::iterator
        v{bookstore.begin()};

    // pause
    system("pause");
    return 0;
}