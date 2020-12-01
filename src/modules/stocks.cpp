#include <iostream>
#include <iomanip> // For decimal places
#include <algorithm>
#include <curl/curl.h>
#include <cstdio>
#include <jsoncpp/json/json.h>
#include <sstream>
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
        cout << fixed << setprecision(2) << data[0].get("price", 0).asFloat() << endl;
        stockInfo.push_back(data);
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
    std::cout << "Started populating Stocks Module" << std::endl;

    // Iterate through vector (only available in C++ 11 or greater)
    for (auto i : this->stocks)
    {
        std::cout << i << std::endl;
        this->stockLabels.push_back(Gtk::Label("Asd"));
    }

    // Iterate through labels
    for (vector<Gtk::Label>::iterator it = this->stockLabels.begin(); it != this->stockLabels.end(); ++it)
    {
        this->box.pack_start(*it, Gtk::PACK_SHRINK, 0);
    }

    this->currentTime = Gtk::Label("Test CSS");
    this->currentTime.get_style_context()->add_class("bold");

    this->box.pack_start(this->currentTime, Gtk::PACK_SHRINK, 0);

    std::cout << "Finished populating Stocks Module" << std::endl;
}