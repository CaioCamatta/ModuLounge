#include <iostream>
#include <iomanip>
#include <algorithm>
#include <curl/curl.h>
#include <cstdio>
#include <jsoncpp/json/json.h>
#include <sstream>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include "stocks.h"
using namespace std;

// Constructor
Stocks::Stocks(const vector<string> stocks, string name, int x, int y) : Module(name, x, y)
{
    this->stocks = stocks;
    initializeStocks(stocks);
};

Stocks::~Stocks() {}

// Write Callback for libcurl API call
std::size_t Stocks::WriteCallback(
    const char *in,
    size_t size,
    size_t num,
    char *out)
{
    string data(in, (std::size_t)size * num);
    *((stringstream *)out) << data;
    return size * num;
}

// Display the Stocks of the specified stock upon creation
void Stocks::initializeStocks(vector<string> stocks)
{
    vector<Json::Value> stockInfo;
    Json::Value data;
    for (vector<string>::iterator it = stocks.begin(); it != stocks.end(); ++it)
    {
        data = fetchStock(*it);

        if (!data[0]["price"])
        {
            throw string("Stock ticker " + *it + " does not exist");
        }

        // Get price as float with 2 decimal points of precision
        stockInfo.push_back(data[0]);
    }
    this->stockInfo = stockInfo;
}

// Get up-to-date stock information from Financial Modeling Prep API
Json::Value Stocks::fetchStock(string stock)
{
    const string API_KEY = "bffb7d7b619c5a34c6d9b31f9ee2e289";
    const string url = "https://financialmodelingprep.com/api/v3/profile/" + stock + "?apikey=" + API_KEY;

    // Curl the data
    CURL *curl = curl_easy_init();
    stringstream httpData;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Stocks::WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // Parse JSON
    Json::Value jsonData;
    Json::CharReaderBuilder jsonReader;
    string errs;
    if (Json::parseFromStream(jsonReader, httpData, &jsonData, &errs))
    {
        return jsonData;
    }
    throw string("Stocks API call failed");
}

void Stocks::populateModule()
{
    // Use a vertical box for this module
    this->box.set_orientation(Gtk::ORIENTATION_VERTICAL);

    // Iterate through vector (only available this way in C++ 11 or greater)
    for (auto i = this->stocks.begin(); i != this->stocks.end(); ++i)
    {
        auto temp_label = new Gtk::Label(); // Use 'new' objects whose lifetime is not necessarily limited by the scope in which they were created.

        boost::to_upper(*i);

        // Round price to two decimals
        float price = this->stockInfo.at(0).get("price", 0).asFloat();
        stringstream stream;
        stream << fixed << setprecision(2) << price;
        string roundPrice = stream.str();

        // Show TICKER:price
        temp_label->set_markup("<b>" + *i + ":</b> " + roundPrice);
        temp_label->set_halign(Gtk::ALIGN_START);
        temp_label->get_style_context()->add_class("my-custom-yellow-color");

        this->box.pack_start(*(temp_label), Gtk::PACK_SHRINK, 3);
    }

    // Also show current date/time based on current system
    time_t now = time(0);
    string dt = ctime(&now);
    this->currentTime = Gtk::Label();
    this->currentTime.set_markup("<small>Last updated " + dt.substr(11, 8) + "</small>");
    this->box.pack_start(currentTime, Gtk::PACK_SHRINK, 3);

    std::cout << " :: Done populating stocks module." << std::endl;
}