// Exercise9.46.cpp
// Ad
// Rewrite the previous exercise using a position and length to manage the strings.
// This time use only the insert function.

#include <iostream>
#include <string>
using std::string;

// function --------------------------------------------------------------------

string function(string n, const string pre, const string suf)
{
    if (!pre.empty())
        n.insert(0, pre + ' ');
    if (!suf.empty())
        n.insert(n.size(), ' ' + suf);
    return n;
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    string name{"Strange"};
    string prefix{"Dr."}, suffix{"I"};
    std::cout << function(name, prefix, suffix) << std::endl;

    // pause
    system("pause");
    return 0;
}