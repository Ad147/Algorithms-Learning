// Exercise9.43.cpp
// Ad
// Write a function that takes three strings, s, oldVal and newVal.
// Using iterators and the insert and erase functions replace all instance of oldVal that appear in s by newVal.
// Test your function by using it to replace common abbreviations, such as "tho" by "though" and "thru" by "through".

#include <iostream>
#include <string>
using std::string;

// function --------------------------------------------------------------------

void function(string &s, const string oldVal, const string newVal)
{
    size_t len{oldVal.size()};
    auto nb{newVal.begin()}, ne{newVal.end()};
    for (auto index{s.begin()}; index != s.end() - len; ++index)
    {
        string str{index, index + len};
        if (str == oldVal)
        {
            s.erase(index, index + len);
            s.insert(index, nb, ne);
        }
    }
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    string s{"thru some string thru the end"};
    function(s, "thru", "through");
    std::cout << s << std::endl;

    // pause
    system("pause");
    return 0;
}