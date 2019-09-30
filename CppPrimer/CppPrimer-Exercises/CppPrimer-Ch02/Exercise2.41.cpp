//  Exercise2.41.cpp
//  Ad
//  Rewrite the exercise in 1.5.1, 1.5.2 and 1.6 using your class.

#include <iostream>
#include <string>

void exercise1_20();
void exercise1_21();
void exercise1_22();
void exercise1_23();
void exercise1_24();
void exercise1_25();

struct SaleData
{
    std::string ISBN;
    int numberSold{0};
    double revenue{0};
};

int main()
{
    exercise1_20();
    exercise1_21();
    exercise1_22();
    exercise1_23();
    exercise1_25();

    //  Pause
    system("pause");
    return 0;
}

void exercise1_20()
{
    SaleData data1;
    int cnt{0};
    while (std::cin >> data1.ISBN >> data1.numberSold >> data1.revenue)
    {
        ++cnt;
        std::cout << std::endl
                  << "Book" << cnt << std::endl
                  << "ISBN: \t" << data1.ISBN << std::endl
                  << "Sold: \t" << data1.numberSold << std::endl
                  << "Revenue:" << data1.revenue << std::endl;
    }
}

void exercise1_21()
{
    SaleData data1, data2;
    std::cin >> data1.ISBN >> data1.numberSold >> data1.revenue;
    std::cin >> data2.ISBN >> data2.numberSold >> data2.revenue;
    if (data1.ISBN == data2.ISBN)
    {        
        std::cout << std::endl
                  << "Sum of 2 books" << std::endl
                  << "ISBN: \t" << data1.ISBN << std::endl
                  << "Sold: \t" << data1.numberSold + data2.numberSold << std::endl
                  << "Revenue:" << data1.revenue + data2.revenue << std::endl;
    }
    else
    {
        std::cout << "Not the same book." << std::endl;
    }
}

void exercise1_22()
{
    SaleData dataSum, data1;
    if (std::cin >> dataSum.ISBN >> dataSum.numberSold >> dataSum.revenue)
    {
        while (std::cin >> data1.ISBN >> data1.numberSold >> data1.revenue)
        {
            if (dataSum.ISBN == data1.ISBN)
            {
                dataSum.numberSold += data1.numberSold;
                dataSum.revenue += data1.revenue;
            }
            else
            {
                std::cout << "Not the same book." << std::endl;
            }
        }
        std::cout << std::endl
                    << "Sum of the books" << std::endl
                    << "ISBN: \t" << dataSum.ISBN << std::endl
                    << "Sold: \t" << dataSum.numberSold << std::endl
                    << "Revenue:" << dataSum.revenue << std::endl;

    }
    else
    {
        std::cout << "No input." << std::endl;
    }
}

void exercise1_23()
{
    SaleData currentData, data1;
    if (std::cin >> currentData.ISBN >> currentData.numberSold >> currentData.revenue)
    {
        int cnt{1};
        while (std::cin >> data1.ISBN >> data1.numberSold >> data1.revenue)
        {
            if (currentData.ISBN == data1.ISBN)
            {
                ++cnt;
            }
            else
            {
                std::cout << "Book with ISBN: " << currentData.ISBN << " occurs " << cnt << " time(s)" << std::endl;
                currentData.ISBN = data1.ISBN;
                currentData.numberSold = data1.numberSold;
                currentData.revenue = data1.revenue;
                cnt = 1;
            }
        }
        std::cout << "Book with ISBN: " << currentData.ISBN << " occurs " << cnt << " time(s)" << std::endl;
    }
    else
    {
        std::cout << "No input." << std::endl;
    }
}

void exercise1_25()
{
    SaleData totalData;
    if (std::cin >> totalData.ISBN >> totalData.numberSold >> totalData.revenue)
    {
        SaleData data1;
        while (std::cin >> data1.ISBN >> data1.numberSold >> data1.revenue)
        {
            if (totalData.ISBN == data1.ISBN)
            {
                totalData.numberSold += data1.numberSold;
                totalData.revenue += data1.revenue;
            }
            else
            {
                std::cout << std::endl
                          << "Sum of the books" << std::endl
                          << "ISBN: \t" << totalData.ISBN << std::endl
                          << "Sold: \t" << totalData.numberSold << std::endl
                          << "Revenue:" << totalData.revenue << std::endl;
                totalData.ISBN = data1.ISBN;
                totalData.numberSold = data1.numberSold;
                totalData.revenue = data1.revenue;
            }
        }
        std::cout << std::endl
                  << "Sum of the books" << std::endl
                  << "ISBN: \t" << totalData.ISBN << std::endl
                  << "Sold: \t" << totalData.numberSold << std::endl
                  << "Revenue:" << totalData.revenue << std::endl;
    }
    else
    {
        std::cout << "No input." << std::endl;
    }
}
