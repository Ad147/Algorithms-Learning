//  Exercise1.17.cpp
//  Ad
//  What happens in the program presented in this section if the  input values are all equal? What if there are no duplicated values?

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