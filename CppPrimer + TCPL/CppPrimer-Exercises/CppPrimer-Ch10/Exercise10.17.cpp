// Exercise10.17.cpp
// Ad
// Rewrite exercise 10.12 to use a lambda in the call to sort instead of the compareIsbn function.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// class -----------------------------------------------------------------------

class Sales_data
{
  public:
    Sales_data(std::string s) : bookNum(s) {}

    std::string isbn() const { return bookNum; }

  private:
    std::string bookNum;
};

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<Sales_data> vec{{"bookA"}, {"bookC"}, {"bookB"}, {"bookA"}};

    sort(vec.begin(), vec.end(),
         [](const Sales_data &data1,
            const Sales_data &data2) { return data1.isbn() < data2.isbn(); });

    for (const auto &s : vec)
        std::cout << s.isbn() << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}