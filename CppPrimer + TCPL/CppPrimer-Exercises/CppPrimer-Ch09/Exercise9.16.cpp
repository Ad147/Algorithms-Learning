// Exercise9.16.cpp
// Ad
// Repeat the previous program, but compare elements in a list<int> to a vector<int>.

#include <iostream>
#include <vector>
#include <list>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 2};
    std::list<int> ilst{1, 1};
    bool flag{1};
    std::vector<int>::const_iterator vit{ivec.begin()};
    std::list<int>::const_iterator lit{ilst.begin()};
    if (ivec.size() == ilst.size())
    {
        for (; vit != ivec.end(); ++vit, ++lit)
        {
            if (*vit != *lit)
            {
                flag = 0;
                break;
            }
        }
    }
    else
    {
        flag = 0;
    }
    std::cout << (flag ? "Equal." : "Not equal.") << std::endl;

    // pause
    system("pause");
    return 0;
}