//  Exercise6.38.cpp
//  Ad
//  Revise the arrPtr function on to return a reference to the array.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

const int odd[] = {1, 3, 5, 7, 9};
const int even[] = {0, 2, 4, 6, 8};

const decltype(odd) &arrPtr(int i)
{
    return (i % 2) ? odd : even;
}

int main(int argc, char* argv[])
{

    //  pause
    cin.get();
    return 0;
}