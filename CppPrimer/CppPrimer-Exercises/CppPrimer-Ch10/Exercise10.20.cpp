// Exercise10.20.cpp
// Ad
// Use count_if to rewrite the portion of our program that counted how many words are greater than length 6.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::string> svec{"a", "asdfghj", "123", "uoiwersss"};
    size_t sz{6};
    auto cnt{count_if(svec.begin(), svec.end(), [sz](const std::string &s) { return s.size() > sz; })};
    std::cout << cnt << std::endl;

    // pause
    system("pause");
    return 0;
}