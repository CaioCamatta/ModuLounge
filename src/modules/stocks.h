#ifndef STOCKS_H
#define STOCKS_H

#include <iostream>
#include "../module.h"

class Stocks : public Module
{
private:
    void initializeStocks(std::vector<std::string> stocks);

public:
    Stocks(const std::vector<std::string> stocks, std::string name, int x, int y) : Module(name, x, y)
    {
        initializeStocks(stocks);
    };
    ~Stocks(){};
    
    void populateModule(); // Add new stuff to the module.

    Json::Value fetchStock(std::string stock);

    // Writer callback for libcurl
    static std::size_t WriteCallback(const char *in, std::size_t size, std::size_t num, char *out);
};

#endif //STOCKS_H
