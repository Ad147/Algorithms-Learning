//  Exercise5.12.cpp
//  Ad
//  Modify your program so that it counts the number of ff, fl, and fi.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned cntA = {0}, cntE = {0}, cntI = {0}, cntO = {0}, cntU = {0}, cntOther = {0};
    unsigned cntSpace = {0}, cntTab = {0}, cntEnter = {0};
    unsigned cntff = {0}, cntfl = {0}, cntfi = {0};
    char cha = {'\0'}, chaLast = {'\0'};
    //  notice the using of cin.get() instead of cin >>
    //  so that the special characters can be read
    while (cin.get(cha))
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
                if (chaLast == 'f')
                {
                    ++cntfi;
                }
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
            case ' ':
                ++cntSpace;
                break;
            case '\t':
                ++cntTab;
                break;
            case '\n':
                ++cntEnter;
                break;
            case 'f':
                if (chaLast == 'f')
                {
                    ++cntff;
                }
                ++cntOther;
                break;
            case 'l':
                if (chaLast == 'f')
                {
                    ++cntfl;
                }
                ++cntOther;
                break;
            default:
                ++cntOther;
                break;
        }
        chaLast = cha;
    }
    cout << "Number of vowel a/A: \t" << cntA << endl
         << "Number of vowel e/E: \t" << cntE << endl
         << "Number of vowel i/I: \t" << cntI << endl
         << "Number of vowel o/O: \t" << cntO << endl
         << "Number of vowel u/U: \t" << cntU << endl
         << "Number of spaces: \t" << cntSpace << endl
         << "Number of tabs: \t" << cntTab << endl
         << "Number of newlines: \t" << cntEnter << endl
         << "Number of ff: \t" << cntff << endl
         << "Number of fl: \t" << cntfl << endl
         << "Number of fi: \t" << cntfi << endl
         << "Number of other: \t" << cntOther << endl;

    //  pause
    system("pause");
    return 0;
}