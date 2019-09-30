//  Exercise5.14.cpp
//  Ad
//  Write a program to read strings and look for duplicated words.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::string str = {}, wordLast = {}, wordDup = {};
    unsigned cnt = {1}, max = {0};
    while (cin >> str)
    {
        if (str == wordLast)
        {
            ++cnt;
        }
        else
        {
            cnt = 1;
        }
        if (max < cnt)
        {
            max = cnt;
            wordDup = str;
        }
        wordLast = str;
    }
    if (max < 2)
    {
        cout << "No word was repeated." << endl;
    }
    else
    {
        cout << "The maximum number of duplicates: " << max << " and the word is " << wordDup << endl;
    }

    //  pause
    system("pause");
    return 0;
}