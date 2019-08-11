// Exercise9.20.cpp
// Ad
// Write a program to copy elements from a list<int> into two deques.
// The even-valued elements should go into one deque and the odd ones into the other.

#include <iostream>
#include <deque>
#include <list>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::list<int> lst{1, 2, 3, 4, 5};
    std::deque<int> deqEven, deqOdd;
    for (auto i : lst)
    {
        if (i % 2 == 0)
            deqEven.push_back(i);
        else
            deqOdd.push_back(i);
    }
    for (auto i : deqEven)
        std::cout << i << ' ';
    std::cout << std::endl;
    for (auto i : deqOdd)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}