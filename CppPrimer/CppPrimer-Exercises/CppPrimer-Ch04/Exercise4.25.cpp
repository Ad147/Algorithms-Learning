//  Exercise4.25.cpp
//  Ad
//  What is value of ~'q'<<6 on a machine with 32-bit ints and 8-bit chars.

#include <iostream>
#include <bitset>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "'q': " << std::bitset<8>('q') << endl;
    cout << "~'q'<<6: " << std::bitset<32>(~'q' << 6) << endl;

    //  pause
    cin.get();
    return 0;
}