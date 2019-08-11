//  Exercise1.18.cpp
//  Ad
//  Compile and run the program from this section giving it only equal values as input. Run it again giving it values in which no number is repeated.

#include <iostream>

int main()
{
    int currentValue = 0, value = 0;
    if (std::cin >> currentValue)
    {
        int cnt = 1;
        while (std::cin >> value)
        {
            if (value == currentValue) {++cnt;}
            else
            {
                std::cout << currentValue << " occurs " << cnt << " time(s) " << std::endl;
                currentValue = value;
                cnt = 1;
            }
        }
        std::cout << currentValue << " occurs " << cnt << " time(s) " << std::endl;
    }
    
    //  Pause
    system("pause");
    return 0;
}