//  Exercise3.13.cpp
//  Ad
//  How many elements are there in each of the following vectors? What are the values of the elements?

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    vector<int> v1;                 //  Empty
    vector<int> v2(10);             //  10 elements with value 0
    vector<int> v3(10, 42);         //  10 elements with value 42
    vector<int> v4{10};             //  1 element with value 10
    vector<int> v5{10, 42};         //  2 elements with value 10 and 42
    vector<string> v6{10};          //  10 elements with empty string
    vector<string> v7{10, "hi"};    //  10 elements with value "hi"

    //  Pause
    cin.get();
    return 0;
}