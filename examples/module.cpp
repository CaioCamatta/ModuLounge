#include "module.h"
#include <gtkmm.h>
#include <iostream>

MyModule::MyModule(Gtk::Window *window)
{
    std::cout << "Creating custom component" << std::endl;
    Gtk::Button button("Btn");
    button.show();
    window->add(button);
}