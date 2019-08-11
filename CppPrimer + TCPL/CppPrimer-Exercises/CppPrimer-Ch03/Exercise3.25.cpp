//  Exercise2.25.cpp
//  Ad
//  Rewrite the grade clustering program using iterator.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<unsigned> scores(11, 0);
    unsigned grade;
    while (cin >> grade)
    {
        if (grade <= 100)
            ++*(scores.begin() + grade / 10);
    }
    for (auto uiter{scores.cbegin()}; uiter != scores.cend(); ++uiter)
        cout << *uiter << ' ';
    cout << endl;

    //  pause
    system("pause");
    return 0;
}