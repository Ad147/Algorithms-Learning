//  Exercise.cpp
//  Ad
//  

#include <iostream>
#include <initializer_list>
using std::cin;
using std::cout;
using std::endl;

int sum(std::initializer_list<int> li);

int main(int argc, char* argv[])
{
    cout << sum({1, 2, 3, 4, 5}) << endl;

    //  pause
    cin.get();
    return 0;
}

int sum(std::initializer_list<int> li)
{
    int s = {0};
    for (const auto &i : li)
    {
        s += i;
    }
    return s;
}