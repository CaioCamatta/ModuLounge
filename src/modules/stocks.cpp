#include <iostream>
#include <iomanip> // For decimal places
#include <algorithm>
#include <curl/curl.h>
#include <cstdio>
#include <jsoncpp/json/json.h>
#include <sstream>
#include "stocks.h"
using namespace std;

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
void Stocks::initializeStocks(string stock)
{
    Json::Value data = fetchStocks(stock);
    if (!data[0]["price"])
    {
        throw string("Stock ticker does not exist");
    }
    // Get price as float with 2 decimal points of precision
    std::cout << std::fixed << std::setprecision(2) << data[0].get("price", 0).asFloat() << endl;
}

// Get up-to-date stock information from Financial Modeling Prep API
Json::Value Stocks::fetchStocks(string stock)
{
    const string API_KEY = "bffb7d7b619c5a34c6d9b31f9ee2e289";
    const string url = "https://financialmodelingprep.com/api/v3/profile/" + stock + "?apikey=" + API_KEY;
    cout << url << endl;

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

    std::cout << "Finished populating Stocks Module" << std::endl;
}