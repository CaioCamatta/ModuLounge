#ifndef MODULE_H
#define MODULE_H

#include <gtkmm.h>

class Module
{
protected:
    int width, height;
    std::string name;

public:
    Module(std::string name, int width, int height);
    int getWidth();
    int getHeight();
    Gtk::Frame frame;
    Gtk::Box box;
};

#endif //MODULE_H