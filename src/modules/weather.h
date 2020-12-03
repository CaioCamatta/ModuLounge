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
    /**
     * @brief Sets the weather information.
     * Calls the fetchWeather function to call API. Goes through resulting JSON
     * and sets necessary class variables about the temperature.
     */
    void getWeather();

    /**
     * @brief Fetch the weather from OpenWeather.
     * Using the specified location, call the OpenWeather API using libcurl. The location can be either a city
     * or a city followed by a comma and 2-character country code. Units for temperatures are specified to Celsius.
     * @return The JSON of all the data received from the libcurl API call
     */
    Json::Value fetchWeather();

    /**
     * @brief Intermittently refresh the module display.
     * This function will re-get the weather then call the redraw function to draw the module
     * again with potentially updated information. It will do this every 20 seconds.
     */
    void refresher();

    /**
     * @brief Redraw the module display.
     * Using the GTK elements defined in the populateModule method, update the text and icon to reflect
     * any data that has changed since the most recent API call.
     */
    void redraw();

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
    static std::size_t writer(const char* in, std::size_t size, std::size_t num, char* out);


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
    Weather(const std::string& location, std::string name, int x, int y) : Module(name, x ,y) {
        this->location = location;
        getWeather();
    };

    /**
     * @brief Destructor.
     * Destroys the instance.
     */
    ~Weather();

    /**
     * @brief Create the UI of the module.
     * Called after all the modules are configured, this function will draw out the information to be seen.
     * This function uses GTK elements to display text which includes the temperature, location, 'feels-like,' and
     * weather description; along with an icon representing the weather. This function will finish by calling (by thread) the refresher.
     */
    void populateModule();
};


#endif //WEATHER_H
