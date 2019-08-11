//  Exercise3.21.cpp
//  Ad
//  Redo the forst exercise from p.105 using iterators.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    //  Code for exercise 3.13
    vector<int> v1;                 //  Empty
    vector<int> v2(10);             //  10 elements with value 0
    vector<int> v3(10, 42);         //  10 elements with value 42
    vector<int> v4{10};             //  1 element with value 10
    vector<int> v5{10, 42};         //  2 elements with value 10 and 42
    vector<string> v6{10};          //  10 elements with empty string
    vector<string> v7{10, "hi"};    //  10 elements with value "hi"
    //  Print the vector sizes
    cout << "Size:" << endl
         << "v1\t"
         << "v2\t"
         << "v3\t"
         << "v4\t"
         << "v5\t"
         << "v6\t"
         << "v7" << endl;
    cout << v1.size() << "\t"
         << v2.size() << "\t"
         << v3.size() << "\t"
         << v4.size() << "\t"
         << v5.size() << "\t"
         << v6.size() << "\t"
         << v7.size() << endl;
    //  print v2
    cout << "v2:" << endl;
    for (auto it{v2.cbegin()}; it != v2.cend(); ++it)
        cout << *it << ' ';
    cout << endl;
    //  print v3
    cout << "v3:" << endl;
    for (auto it{v3.cbegin()}; it != v3.cend(); ++it)
        cout << *it << ' ';
    cout << endl;
    //  print v4 and v5
    cout << "v4: " << *v4.cbegin() << endl;
    cout << "v5: " << *v5.cbegin() << ' ' << *++v5.cbegin() << endl;
    //  print v6
    cout << "v6:" << endl;
    for (auto it{v6.cbegin()}; it != v6.cend(); ++it)
        cout << *it << ' ';
    cout << endl;
    //  print v7
    cout << "v7:" << endl;
    for (auto it{v7.cbegin()}; it != v7.cend(); ++it)
        cout << *it << ' ';
    cout << endl;
    

    //  Pause
    cin.get();
    return 0;
}