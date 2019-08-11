//  Exercise5.10.cpp
//  Ad
//  Write a program that counts both lower- and uppercase letter as the appropriate vowel.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned cntA = {0}, cntE = {0}, cntI = {0}, cntO = {0}, cntU = {0}, cntOther = {0};
    char cha = {};
    while (cin >> cha)
    {
        switch (cha)
        {
            case 'a':
            case 'A':
                ++cntA;
                break;
            case 'e':
            case 'E':
                ++cntE;
                break;
            case 'i':
            case 'I':
                ++cntI;
                break;
            case 'o':
            case 'O':
                ++cntO;
                break;
            case 'u':
            case 'U':
                ++cntU;
                break;
            default:
                ++cntOther;
                break;
        }
    }
    cout << "Number of vowel a/A: \t" << cntA << endl
         << "Number of vowel e/E: \t" << cntE << endl
         << "Number of vowel i/I: \t" << cntI << endl
         << "Number of vowel o/O: \t" << cntO << endl
         << "Number of vowel u/U: \t" << cntU << endl
         << "Number of other: \t" << cntOther << endl;

    //  pause
    system("pause");
    return 0;
}