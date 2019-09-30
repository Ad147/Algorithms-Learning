// Exercise9.27.cpp
// Ad
// Write a program to find and remove the odd-valued elements in a forward_list<int>.

#include <iostream>
#include <forward_list>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::forward_list<int> iflst{1, 2, 3, 4, 5};
    auto preit = iflst.before_begin();
    auto curit = iflst.begin();
    while (curit != iflst.end())
    {
        if (*curit % 2)
            curit = iflst.erase_after(preit);
        else
        {
            preit = curit;
            ++curit;
        }
    }
    for (auto i : iflst)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}