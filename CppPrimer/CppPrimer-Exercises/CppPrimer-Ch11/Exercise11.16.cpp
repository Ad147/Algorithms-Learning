// Exercise11.16.cpp
// Ad
// Using a map iterator write an expression that assigns a value to an element.

#include <iostream>
#include <map>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<char, int> map1{{'a', 0}};

    auto mapIt{map1.begin()};
    mapIt->second = 1;

    for (const auto &p : map1)
        std::cout << p.first << ' ' << p.second << std::endl;

    // pause
    system("pause");
    return 0;
}