#ifndef SPORT_H
#define SPORT_H

#include <gtkmm.h>
#include <jsoncpp/json/json.h>
#include "../module.h"

class Sport : public Module{
    private:

        struct article
        {
            public:
            Gtk::Label title;
            Gtk::Label author;
            Gtk::Label source;
            Gtk::Label published;
            Gtk::Label description;
        };

        void initializeSports(std::string sport, int refresh);
        Json::Value getSportsNews(std::string sport);
        // the sport/team specified by the user 
        std::string sport;
        Json::Value articles;

    public:
        // Use parent constructor. You may not need to customize this constructor at all.
        // New widgets (buttons, text, etc) are supposed to be created in populateModule(), not the constructor.
        Sport(const std::string& sport, std::string name, int width, int height) : Module(name, width, height){
            this->sport = sport;
            initializeSports(sport, 0);
        };

        ~Sport();

        void populateModule();

        void refresher(std::string sport);

        // widgets to display articles inside the frame 
        article art1, art2, art3;
        Gtk::VBox vboxMain;        
};

#endif