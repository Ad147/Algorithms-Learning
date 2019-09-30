//  Exercise6.42.cpp
//  Ad
//  Give the second parameter of make_plural a default argument fo 's'.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

string make_plural(size_t ctr, const string &word, const string &ending = "s");

int main(int argc, char* argv[])
{
    string str1 = {"success"}, str2 = {"failure"};
    cout << str1 << ' ' << str2 << endl;
    cout << make_plural(2, str1, "es") << ' ' << make_plural(2, str2) << endl;

    //  pause
    cin.get();
    return 0;
}

string make_plural(size_t ctr, const string &word, const string &ending)
{
    return ctr > 1 ? word + ending : word;
}