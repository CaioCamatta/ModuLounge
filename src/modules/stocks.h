#ifndef STOCKS_H
#define STOCKS_H
#ifndef REFRESH_RATE
#define REFRESH_RATE 100

#include <iostream>
#include "../module.h"

/**
* @author Caio C. Coelho <ccoelho6@uwo.ca>
* @class Stocks
* @brief A subclass of the Module class to display stock prices.
* The Stocks class creates a components that displays up to three
* up-to-date stock prices from an API. The user is expected to
* enter the names of the tickers (e.g. TSLA). The module updates 
* the prices on regular intervals
*/
class Stocks : public Module
{
private:
    /**
    * Initializes the Stocks module. Fetches data bases on the stocks passed as parameters
    * and stores it in this->stockInfo.
    * 
    * @param stocks vector<string> containing stock tickers (e.g. "AAPL")
    * @brief initialize stock variables and fetch initial data.
    */
    void initializeStocks(std::vector<std::string> stocks);

    // Member Widgets
    std::vector<Gtk::Label> stockLabels;
    std::vector<Json::Value> stockInfo;
    std::vector<std::string> stocks;

public:
    /**
    * Main constructor. Inherits from Module and initializes the stock prices. 
    *  
    * @param stocks vector<string> containing stock tickers (e.g. "AAPL")
    * @param name name of the module and frame in which it lives
    * @param width min requested width for the module
    * @param height min requested height for the module
    * @brief Main constructor
    */
    Stocks(const std::vector<std::string> stocks, std::string name, int width, int height);

    /**
    * Main destructor.
    * @brief Main destructor
    */
    ~Stocks();

    /**
    * Creates visual Widgets for the stock information stored in this module.
    * Only called after the setup Wizard is complete.
    *  
    * @brief Visually displays information stored in this module.
    */
    void populateModule();

    /**
    * Fetches precise, up-to-date data about a particular stock and returns it as JSON object. 
    *  
    * @param stock string containing a stock ticker (e.g. "AAPL")
    * @return Json::Value object containg information about the stock, including 'price'
    * @brief Fetches data about a particular stock
    */
    Json::Value fetchStock(std::string stock);

    /**
    * Standard callback function called by libcurl when data is received. 
    *  
    * @param in char pointer the received data
    * @param size site_t to multiply by num; always 1
    * @param num size_t size of the data received
    * @param out user pointer
    * @return size_t the number of bytes taken care of by the function
    * @brief Standard callback function called by libcurl when data is received
    */
    static std::size_t WriteCallback(const char *in, std::size_t size, std::size_t num, char *out);

    /**
    * Updates the stocks prices with current data. Replaces each Widget in this->box.
    *  
    * @brief Updates the stocks prices with current data 
    */
    void refreshPrices();

    /**
    * Runs refreshPrices every REFRESH_RATE seconds. 
    *  
    * @brief Runs refreshPrices() periodically
    */
    void refresher();
};

#endif //STOCKS_H
#endif //REFRESH_RATE
