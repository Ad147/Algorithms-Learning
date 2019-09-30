// Exercise11.10.cpp
// Ad
// Could we define a map from vector<int>::iterator to int?
// What about from list<int>::iterator to int ?
// In each case, if not, why not?

#include <iostream>
#include <vector>
#include <list>
#include <map>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::vector<int>::iterator, int> map1;
    std::map<std::list<int>::iterator, int> map2;

    // pause
    system("pause");
    return 0;
}