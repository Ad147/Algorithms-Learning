//  Exercise4.31.cpp
//  Ad
//  Rewrite the program in this section using postfix operators.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> ivec(10);
    std::vector<int>::size_type cnt = ivec.size();
    for (std::vector<int>::size_type ix = 0; ix != ivec.size(); ix++, cnt--)
    {
        ivec[ix] = cnt;
    }
    for (int i : ivec)
        cout << i << endl;

    //  pause
    cin.get();
    return 0;
}