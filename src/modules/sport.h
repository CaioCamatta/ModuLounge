#ifndef SPORT_H
#define SPORT_H

#include <gtkmm.h>
#include "../module.h"

class Sport : public Module{
    private:
        void initializeSports(std::string sport);
    public:
        // Use parent constructor. You may not need to customize this constructor at all.
        // New widgets (buttons, text, etc) are supposed to be created in populateModule(), not the constructor.
        Sport(const std::string& sport, std::string name, int width, int height) : Module(name, width, height){
            initializeSports(sport);
        };

        ~Sport();

        void populateModule(); // Add new stuff to the module.

        // Signal handlers:
        void on_button_clicked();

        // Member widgets:
        Gtk::Button button; // All of your widgets need to be data members
};

#endif