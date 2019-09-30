// Exercise9.44.cpp
// Ad
// Rewrite the previous function using an index and replace.

#include <iostream>
#include <string>
using std::string;

// function --------------------------------------------------------------------

void function(string &s, const string oldVal, const string newVal)
{
    size_t len{oldVal.size()};
    for (size_t index{0}; index != s.size() - len; ++index)
    {
        if (s.substr(index, len) == oldVal)
            s.replace(index, len, newVal);
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