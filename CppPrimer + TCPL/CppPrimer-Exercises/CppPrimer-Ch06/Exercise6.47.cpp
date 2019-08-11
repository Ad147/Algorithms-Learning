//  Exercise6.47.cpp
//  Ad
//  Revise the program that used recursion to print the contents of a vector to conditionally print information about its execution.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

void recPrint(std::vector<int>::iterator beg, std::vector<int>::iterator end);

int main(int argc, char* argv[])
{
    std::vector<int> ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    recPrint(ivec.begin(), ivec.end()-1);  //  passing the iterators to the first and the last elements

    //  pause
    cin.get();
    return 0;
}

void recPrint(std::vector<int>::iterator beg, std::vector<int>::iterator end)
{
    #ifndef NDEBUG
    std::cerr << __func__ << ": array size is " << end - beg + 1 << endl;
    #endif
    if (beg != end)
    {
        recPrint(beg, end - 1);
    }
    cout << *end << ' ';
}