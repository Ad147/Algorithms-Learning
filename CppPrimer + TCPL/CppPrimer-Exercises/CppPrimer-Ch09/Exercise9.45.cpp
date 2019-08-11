// Exercise9.45.cpp
// Ad
// Write a function that takes a string representing a name and two other strings representing a prefix, such as "Mr." or "Ms." and a suffix, such as "Jr." or "III".
// Using iterators and the insert and append functions, generate and return a new string with the suffix and prefix added to the given name.

#include <iostream>
#include <string>
using std::string;

// function --------------------------------------------------------------------

string function(string n, const string pre, const string suf)
{
    if (!pre.empty())
    {
        n.insert(n.begin(), ' ');
        n.insert(n.begin(), pre.begin(), pre.end());
    }
    if (!suf.empty())
        n.append(' ' + suf);
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