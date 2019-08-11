// Exercise10.24.cpp
// Ad
// Use bind and check_size to find the first element in a vector of ints that has a value greater than the length of a specified string value.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

// function --------------------------------------------------------------------

bool check_size(const std::string &s, size_t sz)
{
    return s.size() < sz;
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 2, 3, 4, 5};
    std::string s{"abc"};
    auto it{find_if(ivec.begin(), ivec.end(),
                    bind(check_size, s, std::placeholders::_1))};
    std::cout << *it << std::endl;

    // pause
    system("pause");
    return 0;
}