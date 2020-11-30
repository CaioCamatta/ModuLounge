#ifndef SPORT_H
#define SPORT_H

#include <gtkmm.h>
#include <json/json.h>
#include "../module.h"

class Sport : public Module{
    private:
        void initializeSports(std::string sport);

        std::string sport;
        Json::Value articles;

    public:
        // Use parent constructor. You may not need to customize this constructor at all.
        // New widgets (buttons, text, etc) are supposed to be created in populateModule(), not the constructor.
        Sport(const std::string& sport, std::string name, int width, int height) : Module(name, width, height){
            initializeSports(sport);
        };

        ~Sport();

        void populateModule(); // Add new stuff to the module.

        // Member widgets:
        Gtk::Label display1, display2, display3;
        Gtk::VBox vbox;        
};

#endif