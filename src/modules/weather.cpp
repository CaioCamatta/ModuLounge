#include <iostream>
#include <algorithm>
#include <curl/curl.h>
#include <cstdio>
#include <json/json.h> // Use <json/json.h> on mac
#include <sstream>
#include "weather.h"
using namespace std;

Json::Value fetchWeather(string city);

// writer for libcurl API call
std::size_t Weather::writer(
        const char* in,
        size_t size,
        size_t num,
        char* out)
{
    string data(in, (std::size_t) size * num);
    *((stringstream*) out) << data;
    return size * num;
}

// Display the weather of the specified city upon creation
void Weather::initializeWeather(string city) {
    Json::Value data = fetchWeather(city);
    if (!data["name"]) {
        throw string("Location does not exist");
    }
    cout << data["main"]["temp"].asString() << ", " << data["name"].asString() << ", " << data["sys"]["country"].asString() << endl;
}

Weather::~Weather() {

}

// Call the OpenWeatherMap API and return it's results as a Json Value
Json::Value fetchWeather(string city) {
    const string API_KEY = "44a9b4cb7355f31110fed676da845337";
    const string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&units=metric&appid=" + API_KEY;
    CURL* curl = curl_easy_init();
    stringstream httpData;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Weather::writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    Json::Value jsonData;
    Json::CharReaderBuilder jsonReader;
    string errs;

    if (Json::parseFromStream(jsonReader, httpData, &jsonData, &errs))
    {
        return jsonData;
    }
    throw string("API call failed");
}

void Weather::populateModule()
{
    std::cout << "Start populating custom Module" << std::endl;

    // Create a button, with label "Press Me"
    this->button = Gtk::Button("Button");

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    this->button.signal_clicked().connect(sigc::mem_fun(*this,
                                                        &Weather::on_button_clicked));

    // Add Button to our Box (the Box holds all the widgets of this Module)
    // Shrink Widget to its size, add 0 padding
    this->box.pack_start(button, Gtk::PACK_SHRINK,0);

    // Create a second button to demonstrate how multiple widgets can be added to Box
    this->button2 = Gtk::Button("Press Me 2");
    this->button2.signal_clicked().connect(sigc::mem_fun(*this,
                                                         &Weather::on_button_clicked));
    this->box.pack_start(button2);

    std::cout << "Finished populating custom Module" << std::endl;
}

void Weather::on_button_clicked()
{
    std::cout << "Button was pressed." << std::endl;
}