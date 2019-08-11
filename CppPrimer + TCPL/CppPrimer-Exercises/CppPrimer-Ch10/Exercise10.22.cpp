// Exercise10.22.cpp
// Ad
// Rewrite the program to count words of size 6 or less using functions in place of the lambdas.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

// function --------------------------------------------------------------------

bool function(const std::string &s, const size_t n)
{
    return s.size() <= n;
}

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::string> svec{"a", "asdfghj", "123", "uoiwes"};
    size_t sz{6};
    auto cnt{count_if(svec.begin(), svec.end(),
                      bind(function, std::placeholders::_1, sz))};
    std::cout << cnt << std::endl;

    // pause
    system("pause");
    return 0;
}