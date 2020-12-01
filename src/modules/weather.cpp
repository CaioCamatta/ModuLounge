#include <iostream>
#include <algorithm>
#include <curl/curl.h>
#include <cstdio>
#include <json/json.h> // Use <json/json.h> on mac
#include <sstream>
#include "weather.h"
using namespace std;

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
void Weather::getWeather(string location) {
    Json::Value data = fetchWeather(location);
    if (data["cod"].asString() == "404") {
        throw string("Location does not exist");
    }
    this->temp = data["main"]["temp"].asInt();
    this->feels_like = data["main"]["feels_like"].asInt();
    this->city = data["name"].asString();
    this->country = data["sys"]["country"].asString();
    this->desc = data["weather"][0]["main"].asString();
    this->icon = data["weather"][0]["icon"].asString();
}

Weather::~Weather() {

}

// Call the OpenWeatherMap API and return it's results as a Json Value
Json::Value Weather::fetchWeather(string location) {
    const string API_KEY = "44a9b4cb7355f31110fed676da845337";
    const string url = "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&units=metric&appid=" + API_KEY;
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
    cout << "Start populating custom Module" << std::endl;

    this->box.set_size_request(200,100); // Set module size

    // Create text
    Gtk::Label* text = new Gtk::Label();
    text->set_markup(this->city + ", " + this->country + "\n<span size='xx-large'><b>" +
            to_string(this->temp) + "°C</b></span>\nFeels Like: <b>" + to_string(this->feels_like) + "°C</b>\n<i>" +
            this->desc + "</i>");
    this->box.pack_start(*text, true, true);

    // Create image (give error if image not found)
    try {
        Gtk::Image* img = Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file("src/images/" +
                this->icon.substr(0,2) + "d@2x.png")));
        this->box.pack_start(*img);
    } catch (const Glib::FileError& ex) {
        cerr << ex.what() << endl;
    }
}