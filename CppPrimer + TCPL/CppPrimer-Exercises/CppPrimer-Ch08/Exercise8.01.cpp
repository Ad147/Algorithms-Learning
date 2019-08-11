// Exercise8.01.cpp
// Ad
// Write a function that takes and returns an istream&.
// The function should read the stream until it hits end-of-file.
// The function should print what it reads to the standard output.
// Reset the stream so that it is valid before returning the stream.

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
