/** @file weather.cpp */
#include <iostream>
#include <algorithm>
#include <curl/curl.h>
#include <cstdio>
#include <thread>
#include <sstream>
#include "weather.h"
using namespace std;

/**
 * @brief Writer for API call.
 * This function is used by the libcurl API call to write the data from the call.
 *
 * @param in The incoming data
 * @param size The size of a datum
 * @param num The number of data
 * @param out The output for the data
 * @return The write size of all the data
 */
std::size_t Weather::writer(const char* in, size_t size, size_t num, char* out)
{
    string data(in, (std::size_t) size * num);
    *((stringstream*) out) << data;
    return size * num;
}

/**
 * @brief Sets the weather information.
 * Calls the fetchWeather function to call API. Goes through resulting JSON
 * and sets necessary class variables about the temperature.
 */
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

/**
 * @brief Destructor.
 * Destroys the instance.
 */
Weather::~Weather() {

}

/**
 * @brief Fetch the weather from OpenWeather.
 * Using the specified location, call the OpenWeather API using libcurl. The location can be either a city
 * or a city followed by a comma and 2-character country code. Units for temperatures are specified to Celsius.
 * @return The JSON of all the data received from the libcurl API call
 */
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

/**
 * @brief Create the UI of the module.
 * Called after all the modules are configured, this function will draw out the information to be seen.
 * This function uses GTK elements to display text which includes the temperature, location, 'feels-like,' and
 * weather description; along with an icon representing the weather. This function will finish by calling (by thread) the refresher.
 */
void Weather::populateModule()
{
    cout << "Start populating custom Module" << std::endl;

    getWeather(); // Set the information needed

    // Create text
    this->data = Gtk::Label();
    this->data.set_markup(this->city + ", " + this->country + "\n<span size='xx-large'><b>" +
                     to_string(this->temp) + "°C</b></span>\nFeels Like: <b>" + to_string(this->feels_like) + "°C</b>\n<i>" +
                     this->desc + "</i>\n\n");
    this->box.pack_start(this->data);

    // Create image (give error if image not found)
    try {
        this->image = Gtk::Image(Gdk::Pixbuf::create_from_file("src/images/" + this->icon.substr(0,2) + "d@2x.png"));
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

/**
 * @brief Intermittently refresh the module display.
 * This function will re-get the weather then call the redraw function to draw the module
 * again with potentially updated information. It will do this every 20 seconds.
 */
void Weather::refresher() {
    while(true){
        this_thread::sleep_for (chrono::seconds(20));
        getWeather();
        redraw();
    }
}

/**
 * @brief Redraw the module display.
 * Using the GTK elements defined in the populateModule method, update the text and icon to reflect
 * any data that has changed since the most recent API call.
 */
void Weather::redraw()
{
    // Redefine text
    this->data.set_markup(this->city + ", " + this->country + "\n<span size='xx-large'><b>" +
                     to_string(this->temp) + "°C</b></span>\nFeels Like: <b>" + to_string(this->feels_like) + "°C</b>\n<i>" +
                     this->desc + "</i>\n\n");

    // Redefine image (give error if image not found)
    try {
        this->image.set("src/images/" + this->icon.substr(0,2) + "d@2x.png");
    } catch (const Glib::FileError& ex) {
        cerr << ex.what() << endl;
    }
}