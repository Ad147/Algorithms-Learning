#ifndef SALEDATA_H
#define SALEDATA_H

#include <string>

struct SaleData
{
    std::string ISBN;
    int numberSold{0};
    double revenue{0};
};

#endif