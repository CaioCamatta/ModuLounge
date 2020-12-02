#include "module.h"
#include <gtkmm.h>
#include <iostream>

/* Initializes a module with nothing but a frame with a title and an empty box.
This Module can be displayed on its own, but it doesn't have anything, and
is supposed to be inherited and expanded by the child modules*/
Module::Module(std::string name, int width, int height)
{
    this->name = name;
    this->width = width;   // Min Box width
    this->height = height; // Min Box height

    /* Setup Box to hold all our widgets*/
    this->box = Gtk::Box(); // Create Box to contain widgets (buttons, texts, etc)
    this->box.set_size_request(width, height); // Set min width/height

    /* Setup frame that wraps the Box */
    this->frame = Gtk::Frame();
    name[0] = toupper(name[0]);
    this->frame.set_label(name);
    this->frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT); // Specify shadow type
    this->frame.set_border_width(10);
    this->frame.add(box); // Add/"link" box to frame, this only needs to be done once.

    std::cout << " :: Module added." << std::endl;
}

Module::~Module()
{
}

int Module::getHeight()
{
    return this->height;
}

int Module::getWidth()
{
    return this->width;
}

std::string Module::getName()
{
    return this->name;
}