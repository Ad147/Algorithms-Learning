//  Exercise3.24.cpp
//  Ad
//  Redo the last exercise from p.105 using iterators.

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
    for (auto iiter{ivec.cbegin()}; iiter != ivec.cend(); iiter += 2)
    {
        if (iiter != ivec.cend() - 1)
            cout << *iiter + *(iiter + 1) << ' ';
        else
        {
            cout << *iiter;
            break;
        }
    }
    cout << endl;
    //  print the sum of the first and the last and so on
    for (auto iiter{ivec.cbegin()}; iiter != ivec.cbegin() + ivec.size() / 2; ++iiter)
    {
        cout << *iiter + *(ivec.cbegin() + (ivec.cend() - iiter - 1)) << ' ';
    }
    if (ivec.size() % 2 == 1)
        cout << *(ivec.cbegin() + ivec.size() / 2);
    cout << endl;

    //  pause
    system("pause");
    return 0;
}