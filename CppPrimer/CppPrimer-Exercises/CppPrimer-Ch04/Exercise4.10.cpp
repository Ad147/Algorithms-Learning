//  Exercise4.10.cpp
//  Ad
//  Write the conditon for a while loop that read ints and stop when the value read is equal to 42.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int i{0};
    while (cin >> i && i != 42)

    //  pause
    cin.get();
    return 0;
}