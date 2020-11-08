#include "sampleModule.h"
#include <gtkmm.h>
#include <iostream>

void SampleModule::populateModule()
{
    std::cout << "Start populating custom component" << std::endl;

    this->button = Gtk::Button("Btn");
    this->button.show();

    this->box.pack_start(button);
    this->box.set_border_width(20);
    this->box.show(); // Show once box is ready

    this->frame.add(box);

    std::cout << "Finished populating custom component" << std::endl;
}
