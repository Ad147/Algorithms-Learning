//  Exercise6.23.cpp
//  Ad
//  Write you own versions of each of the print functions presented in this section.

#include <iostream>
#include <iterator>
using std::cin;
using std::cout;
using std::endl;

void print(const int *i);
void print(const int *beg,const int *end);

int main()
{
    int i = 0, j[2] = {0, 1};
    print(&i);
    print(j);
    print(std::begin(j), std::end(j));

    //  pause
    cin.get();
    return 0;
}

void print(const int *i)
{
    cout << *i << endl;
}

void print(const int *beg,const int *end)
{
    while (beg != end)
    {
        cout << *beg++ << endl;
    }
}