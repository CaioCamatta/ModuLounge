#include <gtkmm.h>
#include "modules/sampleModule.h"
#include "module.h"
#include <iostream>

int main(int argc, char *argv[])
{
    auto app =
        Gtk::Application::create(argc, argv,
                                 "group54.moduLounge");

    // Create window, set size and border width
    Gtk::Window window;
    window.set_default_size(400, 400);
    window.set_border_width(30);

    // Create grid to house all the Modules/Frames
    Gtk::Grid grid;

    /*  This is how you add a module:
            1. Create the Module
            2. Show() the Frame that contains the actual thigns in the module
            3. Add the frame to the main grid 
    */
    // SampleModule is a basic module with two buttons that print to the terminal when clicked
    SampleModule mySampleModule("Sample Module", 100, 100);
    mySampleModule.populateModule();
    grid.add(mySampleModule.frame);

    // SampleModule2 is a baxic module with two buttons that print to the terminal when clicked
    SampleModule mySampleModule2("Sample Module 2", 100, 50);
    mySampleModule2.populateModule();
    grid.add(mySampleModule2.frame);

    /* Once everything all the Boxes, Buttons, etc have been created and linked,
    we add the Grid to the Window and show all children */
    window.add(grid);
    window.show_all_children();

    return app->run(window);
}