// Exercise10.02.cpp
// Ad
// Repeat the previous program, but read values into a list of strings.

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::list<std::string> slst{"alpha", "beta", "gama", "alpha", "alpha"};
    std::cout << "alpha appears " << count(slst.begin(), slst.end(), "alpha")
              << " times." << std::endl;

    // pause
    system("pause");
    return 0;
}