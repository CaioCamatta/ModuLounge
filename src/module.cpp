#include "module.h"
#include <gtkmm.h>
#include <iostream>

/* Initializes a module with nothing but a frame with a title and an empty box.
This Module can be displayed on its own, but it doesn't have anything, and
is supposed to be inherited and expanded by the child modules*/
Module::Module(std::string name, int x, int y)
{
    this->name = name; // name referred to by wizard
    this->x = x;   // x-coordinate
    this->y = y; // y-coordinate

    /* Setup Box to hold all our widgets*/
    this->box = Gtk::Box(); // Create Box to contain widgets (buttons, texts, etc)
    this->box.set_size_request(530, 400); // Set min width/height

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

int Module::getX()
{
    return this->x;
}

int Module::getY()
{
    return this->y;
}

void Module::setX(int x)
{
    this->x = x;
}

void Module::setY(int y)
{
    this->y = y;
}

std::string Module::getName()
{
    return this->name;
}