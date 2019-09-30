//  Exercise6.30.cpp
//  Ad
//  Compile the str_subrange to see what your compiler does with the indicated errors.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{

    //  pause
    cin.get();
    return 0;
}

bool str_subrange(const std::string &str1, const std::string &str2)
{
    if (str1.size() == str2.size())
        return str1 == str2;
    auto size = (str1.size() < str2.size()) ? str1.size() : str2.size();
    for (decltype(size) i = 0; i != size; ++i)
    {
        if (str1[i] != str2[i])
            return 0;
    }
}  //  compiler gives a warning about no return