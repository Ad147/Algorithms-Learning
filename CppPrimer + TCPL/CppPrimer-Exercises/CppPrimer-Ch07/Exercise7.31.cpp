// Exercise7.31.cpp
// Ad
// Define a pair of classes X and Y, in which X has a pointer to Y, and Y has an
// object of type X.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// declare Y so that the pointer to Y can be defined
class Y;

class X
{
    Y *ptr{nullptr};
};

class Y
{
    X obj;
};

int main(int argc, char* argv[])
{

    // pause
    cin.get();
    return 0;
}