#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <jsoncpp/json/json.h> // Use <json/json.h> on mac
#include "../module.h"

/**
 * @author Jack Hillier
 * @brief Display the weather based on location.
 * This class takes a location and calls the OpenWeather API. The weather and other
 * information is taken from the API, and displayed along with a descriptive image.
 */
class Weather : public Module {
    private:
        void getWeather();
        Json::Value fetchWeather();
        void refresher();
        void redraw();


        Gtk::Label data;
        Gtk::Image image;
        std::string location;
        std::string city;
        std::string country;
        int temp;
        int feels_like;
        std::string desc;
        std::string icon;
    public:
        /**
         * @brief Constructor.
         * Creates the instance and sets location variable for later API call
         *
         * @param location The specified city (with optional country code).
         * @param name The name of the module.
         * @param x The x-coordinate of the module.
         * @param y The y-coordinate of the module.
         */
        Weather(const std::string& location, std::string name, int x, int y) : Module(name, x ,y) { this->location = location; };
        ~Weather();
        void populateModule();

        static std::size_t writer(const char* in, std::size_t size, std::size_t num, char* out);
};


#endif //WEATHER_H
