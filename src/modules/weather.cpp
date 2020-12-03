/** @file weather.cpp */
#include <iostream>
#include <algorithm>
#include <curl/curl.h>
#include <cstdio>
#include <thread>
#include <sstream>
#include "weather.h"
using namespace std;

std::size_t Weather::writer(const char* in, size_t size, size_t num, char* out)
{
    string data(in, (std::size_t) size * num);
    *((stringstream*) out) << data;
    return size * num;
}

void Weather::getWeather() {
    Json::Value data = fetchWeather(); // Do API call

    // Check if the call had no results and if so, throw an error.
    if (data["cod"].asString() == "404") {
        throw string("Location does not exist");
    }

    // Set class variables
    this->temp = data["main"]["temp"].asInt();
    this->feels_like = data["main"]["feels_like"].asInt();
    this->city = data["name"].asString();
    this->country = data["sys"]["country"].asString();
    this->desc = data["weather"][0]["main"].asString();
    this->icon = data["weather"][0]["icon"].asString();
}

Weather::~Weather() {

}

Json::Value Weather::fetchWeather() {

    // Setup API call address
    const string API_KEY = "44a9b4cb7355f31110fed676da845337";
    const string url = "http://api.openweathermap.org/data/2.5/weather?q=" + this->location + "&units=metric&appid=" + API_KEY;

    // libcurl setup
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

    // Take data from the API call
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
    cout << "Start populating custom Module" << std::endl;

    getWeather(); // Set the information needed

    // Create text
    this->data = Gtk::Label();
    this->data.set_markup("<span size='20000'>" + this->city + ", " + this->country + "</span>\n<span size='60000'><b>" +
                     to_string(this->temp) + "°C</b></span>\n<span size='20000'>Feels Like: <b>" + to_string(this->feels_like) + "°C</b>\n<i>" +
                     this->desc + "</i></span>\n\n");
    this->box.pack_start(this->data);

    // Create image (give error if image not found)
    try {
        this->image = Gtk::Image(Gdk::Pixbuf::create_from_file("src/images/" + this->icon.substr(0,2) + "d@2x.png", 200, 200));
        this->image.get_style_context()->add_class("icon");
        this->box.pack_end(this->image);
    } catch (const Glib::FileError& ex) {
        cerr << ex.what() << endl;
    }

    // Create new thread to intermittently redraw module
    thread weather_thread(&Weather::refresher, this);
    weather_thread.detach();

    cout << "Finished populating custom Module" << endl;
}

void Weather::refresher() {
    while(true){
        this_thread::sleep_for (chrono::seconds(20));
        getWeather();
        redraw();
    }
}

void Weather::redraw()
{
    // Redefine text
    this->data.set_markup("<span size='20000'>" + this->city + ", " + this->country + "</span>\n<span size='60000'><b>" +
                     to_string(this->temp) + "°C</b></span>\n<span size='20000'>Feels Like: <b>" + to_string(this->feels_like) + "°C</b>\n<i>" +
                     this->desc + "</i></span>\n\n");

    // Redefine image (give error if image not found)
    try {
        this->image.set(Gdk::Pixbuf::create_from_file("src/images/" + this->icon.substr(0,2) + "d@2x.png", 200, 200));
    } catch (const Glib::FileError& ex) {
        cerr << ex.what() << endl;
    }
}