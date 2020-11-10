#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include "../module.h"

class Weather : public Module {
    private:
        void initializeWeather(std::string city);
    public:
        Weather(const std::string& city, std::string name, int x, int y) : Module(name, x ,y) { initializeWeather(city); };
        ~Weather();
        void populateModule(); // Add new stuff to the module.

        // Signal handlers:
        void on_button_clicked();

        // Member widgets:
        Gtk::Button button, button2; // All of your widgets need to be data members
};


#endif //WEATHER_H
