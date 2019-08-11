// Exercise10.12.cpp
// Ad
// Write a function named compareIsbn that compares the isbn() memebers of two Sales_data objects.
// Use that function to sort a vector that holds Sales_data objects.

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

// function --------------------------------------------------------------------

bool compareIsbn(const Sales_data &dat1, const Sales_data &dat2)
{
    return dat1.isbn() < dat2.isbn();
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<Sales_data> vec{{"bookA"}, {"bookC"}, {"bookB"}, {"bookA"}};
    stable_sort(vec.begin(), vec.end(), compareIsbn);
    for (const auto &s : vec)
        std::cout << s.isbn() << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}