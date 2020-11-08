#ifndef SAMPLEMODULE_H
#define SAMPLEMODULE_H

#include <gtkmm.h>
#include "../module.h"

class SampleModule : public Module
{
public:
    // Use parent constructor. You may not need to customize this constructor at all.
    // New widgets (buttons, text, etc) are supposed to be created in populateModule(), not the constructor.
    SampleModule(std::string name, int width, int height) : Module(name, width, height){};

    void populateModule(); // Add new stuff to the module.

    // Signal handlers:
    void on_button_clicked();

    // Member widgets:
    Gtk::Button button, button2; // All of your widgets need to be data members
};

#endif //SAMPLEMODULE_H