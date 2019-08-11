// Exercise9.28.cpp
// Ad
// Write a function that takes a forward_list<string> and two additional string arguments.
// Ther function should find the first string and insert the seconde immediately following the first.
// If the first is not found, then insert the second string at the end of the list.

#include <iostream>
#include <forward_list>
using std::string;

// function --------------------------------------------------------------------

void function(std::forward_list<string> &lst,
              const string &str1, const string &str2)
{
    auto preit{lst.before_begin()};
    auto curit{lst.begin()};
    bool flag{0};
    for (; curit != lst.end(); ++preit, ++curit)
    {
        if (*curit == str1)
        {
            flag = 1;
            break;
        }
    }
    lst.insert_after((flag ? curit : preit), str2);
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::forward_list<string> slst0{"no", "any", "string"};
    std::forward_list<string> slst1{"some", "string"};
    function(slst0, "some", "tail");
    function(slst1, "some", "tail");
    for (auto s : slst0)
        std::cout << s << ' ';
    std::cout << std::endl;
    for (auto s : slst1)
        std::cout << s << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}