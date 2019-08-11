// Exercise10.32.cpp
// Ad
// Rewrite the bookstore program from p.24 using a vector to hold the transactions and various algorithms to do the processing.
// Use sort with your compareIsbn function to arrange the transactions in order, and then use find and accumulate to do the sum.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>

// class -----------------------------------------------------------------------

class Sales_data
{
  public:
    Sales_data() = default;
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

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    // note that without operator overloading this program does not work

    std::istream_iterator<Sales_data> inIter{std::cin}, eof;
    std::vector<Sales_data> svec{inIter, eof};

    std::sort(svec.begin(), svec.end(), compareIsbn);

    std::ostream_iterator<Sales_data> outIter{std::cout, "\n"};
    auto iter0{svec.begin()}, iter1{svec.begin()};
    while (iter1 != svec.end())
    {
        iter1 = std::find_if(svec.begin(), svec.end(),
                             [&iter1](const Sales_data &d) {
                                 return d.isbn() != iter1->isbn();
                             });
        std::accumulate(iter0, iter1, outIter);
        iter0 = iter1;
    }

    // pause
    system("pause");
    return 0;
}