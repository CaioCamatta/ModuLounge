#ifndef STOCKS_H
#define STOCKS_H

#include <iostream>
#include "../module.h"

class Stocks : public Module
{
private:
    void initializeStocks(std::string stock);

public:
    Stocks(const std::string &stock, std::string name, int x, int y) : Module(name, x, y)
    {
        initializeStocks(stock);
    };
    ~Stocks(){};
    void populateModule(); // Add new stuff to the module.

    Json::Value fetchStocks(std::string stock);

    // Writer callback for libcurl
    static std::size_t WriteCallback(const char *in, std::size_t size, std::size_t num, char *out);
};

#endif //STOCKS_H
