// Exercise8.02.cpp
// Ad
// Test your function by calling it, passing cin as an argument.

#include <iostream>

std::istream &function(std::istream &is)
{
    int i;
    while (is >> i)
    {
        std::cout << i << std::endl;
    }
    is.clear();
    return is;
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    function(std::cin);

    // pause
    system("pause");
    return 0;
}