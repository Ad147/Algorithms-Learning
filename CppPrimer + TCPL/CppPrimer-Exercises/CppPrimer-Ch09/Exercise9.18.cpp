// Exercise9.18.cpp
// Ad
// Write a program to read a sequence of string from the standard input into a deque.
// Use iterators to write a loop to print the elements in the deque.

#include <iostream>
#include <deque>
#include <string>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::deque<std::string> sdeq;
    std::string s;
    while (std::cin >> s)
    {
        sdeq.push_back(s);
    }
    for (auto dit{sdeq.begin()};
         dit != sdeq.end(); ++dit)
        std::cout << *dit << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}