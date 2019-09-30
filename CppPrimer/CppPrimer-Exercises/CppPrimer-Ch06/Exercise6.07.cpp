//  Exercise6.07.cpp
//  Ad
//  Write a function that returns 0 when it is first called and then generates numbers in sequence each time it is called again.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

unsigned countCall();

int main()
{
    for (int i = {0}; i != 10; ++i)
    {
        cout << countCall() << ' ';
    }
    cout << endl;

    //  pause
    cin.get();
    return 0;
}

unsigned countCall()
{
    static unsigned cnt = {0};
    return cnt++;
}