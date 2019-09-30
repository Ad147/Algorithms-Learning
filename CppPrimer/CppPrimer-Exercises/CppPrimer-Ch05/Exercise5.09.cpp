//  Exercise5.09.cpp
//  Ad
//  Write a program using a series of if statements to count the number of vowels in text read from cin.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned cnt = {0};
    char cha = {};
    while (cin >> cha)
    {
        if (cha == 'a')
            ++cnt;
        if (cha == 'e')
            ++cnt;
        if (cha == 'i')
            ++cnt;
        if (cha == 'o')
            ++cnt;
        if (cha == 'u')
            ++cnt;
    }
    cout << "Number of vowels: \t" << cnt << endl;

    //  pause
    system("pause");
    return 0;
}