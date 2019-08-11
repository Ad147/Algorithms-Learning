//  Exercise3.22.cpp
//  Ad
//  Revise the loop that printed the first paragraph in text to instead change the elements in the first paragraph to all uppercase.

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<std::string> text{};
    std::string str{};
    while (cin >> str)
    {
        text.push_back(str);
    }
    for (auto vit{text.begin()}; vit != text.end() && !vit->empty(); ++vit)
    {
        for (auto sit{vit->begin()}; sit != vit->end(); ++sit)
        {
            *sit = toupper(*sit);
        }
        cout << *vit << ' ';
    }
    cout << endl;

    //  pause
    system("pause");
    return 0;
}