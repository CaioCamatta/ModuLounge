#ifndef STOCKS_H
#define STOCKS_H

#include <iostream>
#include "../module.h"

class Stocks : public Module
{
private:
    void initializeStocks(std::vector<std::string> stocks);
    std::vector<Json::Value> stockInfo;
    std::vector<std::string> stocks;

public:
    Stocks(const std::vector<std::string> stocks, std::string name, int x, int y);
    ~Stocks();

    void populateModule();

    Json::Value fetchStock(std::string stock);

    // Writer callback for libcurl
    static std::size_t WriteCallback(const char *in, std::size_t size, std::size_t num, char *out);

    // Member Widgets
    std::vector<Gtk::Label> stockLabels;
    Gtk::Label currentTime;
};

#endif //STOCKS_H
