#include "module.h"
#include <gtkmm.h>
#include <iostream>

Module::Module(std::string name, int width, int height)
{
    std::cout << "Start creation of custom component" << std::endl;
    this->name = name;
    this->width = width;
    this->height = height;
    this->box = Gtk::Box();

    /* Setup frame */
    this->frame = Gtk::Frame();
    this->frame.set_label(name);
    this->frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    this->frame.set_border_width(10);

    std::cout << "Finished creating custom component" << std::endl;
}

int Module::getHeight()
{
    return this->height;
}
int Module::getWidth()
{
    return this->width;
}