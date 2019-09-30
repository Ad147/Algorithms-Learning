// Exercise11.18.cpp
// Ad
// Write the type of map_it from the loop on page 430 without using auto or decltype.

#include <iostream>
#include <string>
#include <map>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, size_t> word_count;

    std::map<std::string, size_t>::const_iterator map_it = word_count.cbegin();

    // pause
    system("pause");
    return 0;
}