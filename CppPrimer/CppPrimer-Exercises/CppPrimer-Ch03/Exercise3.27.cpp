//  Exercise3.27.cpp
//  Ad
//  Which of the following definitions are illegal?

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int txt_size()
{
    return 0;
}

int main()
{
    unsigned bufSize{1024};
    int ia1[bufSize];           //  bufSize should be const
    int ia2[4 * 7 - 14];
    int ia3[txt_size()];        //  the function should return a integer greater than 0
    char st[11]{"fundamental"}; //  the array is not large enough

    //  pause
    cin.get();
    return 0;
}