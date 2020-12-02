#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <jsoncpp/json/json.h> // Use <json/json.h> on mac
#include "../module.h"

class Weather : public Module {
    private:
        void getWeather(std::string location);
        Json::Value fetchWeather(std::string location);
        std::string city;
        std::string country;
        int temp;
        int feels_like;
        std::string desc;
        std::string icon;
    public:
        Weather(const std::string& location, std::string name, int x, int y) : Module(name, x ,y) { getWeather(location); };
        ~Weather();
            void populateModule(); // Add new stuff to the module.

        // Writer callback for libcurl
        static std::size_t writer(const char* in, std::size_t size, std::size_t num, char* out);
};


#endif //WEATHER_H
