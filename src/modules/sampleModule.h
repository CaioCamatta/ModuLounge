#ifndef SAMPLEMODULE_H
#define SAMPLEMODULE_H

#include <gtkmm.h>
#include "../module.h"
class SampleModule : public Module
{
public:
    SampleModule(std::string name, int width, int height) : Module(name, width, height){};
    void populateModule();
    Gtk::Button button;
};

#endif //SAMPLEMODULE_H