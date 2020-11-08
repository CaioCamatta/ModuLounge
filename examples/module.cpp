#include "module.h"
#include <gtkmm.h>
#include <iostream>

Module::Module()
{
    std::cout << "Start creation of custom component" << std::endl;

    this->button = Gtk::Button("Btn");
    this->button.show();

    this->box = Gtk::Box();
    this->box.pack_start(button);
    this->box.set_border_width(20);
    this->box.show(); // Show once box is ready

    /* Set the frames label */
    this->frame = Gtk::Frame();
    this->frame.set_label("Frame Widget");
    this->frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    this->frame.set_border_width(10);

    this->frame.add(box);

    std::cout << "Finished creating custom component" << std::endl;
}
