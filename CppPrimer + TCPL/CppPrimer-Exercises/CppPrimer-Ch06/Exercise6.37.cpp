//  Exercise6.37.cpp
//  Ad
//  Write three declarations using type alias, trailing return and decltype for functions that return a reference to an array of ten strings.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

//  the original
std::string (&function())[10];

//  using type alias
using arrStr = std::string[10];
arrStr &function1();

//  using trailing return
auto function2() -> std::string (&)[10];

//  using decltype
std::string as[10] = {};
decltype(as) &function3();

int main(int argc, char* argv[])
{

    //  pause
    cin.get();
    return 0;
}