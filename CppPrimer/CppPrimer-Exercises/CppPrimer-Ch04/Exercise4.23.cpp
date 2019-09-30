//  Exercise4.23.cpp
//  Ad
//  Explain why the following expression fails to compile then fix it.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::string s = "word";
    // std::string pl = s + s[s.size() - 1] == 's' ? " " : "s";
    std::string pl = s + ((s[s.size() - 1] == 's') ? " " : "s");
    cout << pl << endl;

    //  pause
    cin.get();
    return 0;
}