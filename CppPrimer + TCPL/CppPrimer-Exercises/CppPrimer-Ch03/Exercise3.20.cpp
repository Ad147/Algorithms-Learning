//  Exercise3.20.cpp
//  Ad
//  Read a set of integers in to a vector, print the sum of each pair of adjacent elements. Change the program to print the sum of the first and the last, then the second and the second-to-last and so on.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> ivec{};
    int i{0};
    while (cin >> i)
        ivec.push_back(i);
    //  print the sum of each pair of adjacent integers
    if (!ivec.empty())
    {
        for (decltype(ivec.size()) i{0}; i < ivec.size(); i += 2)
        {
            if (i != ivec.size() - 1)
                cout << ivec[i] + ivec[i + 1] << ' ';
            else
                cout << ivec[i];
        }
        cout << endl;
    }
    //  print the sum of the first and the last and so on
    if (!ivec.empty())
    {
        for (decltype(ivec.size()) i{0}; i < ivec.size() / 2; ++i)
        {
            cout << ivec[i] + ivec[ivec.size() - i - 1] << ' ';
        }
        if (ivec.size() % 2 == 1)
            cout << ivec[ivec.size() / 2];
        cout << endl;
    }

    //  pause
    system("pause");
    return 0;
}