/** @file main.cpp */
#include <iostream>
#include <gtkmm.h>
#include <vector>
#include <memory>
#include "modules/weather.h"
#include "module.h"
#include "wizard.h"
#include "modules/newsModule.h"

/**
* Main function. Creates Gtk application, loads global css, runs Wizard, 
* adds modules to the screen.
*  
* @brief Main function
* @param argc int argument containing the number arguments
* @param argv list of command line arguments
* @return integer 0 on exit success
*/
int main(int argc, char *argv[])
{

    // ------------- UI -----------------
    auto app =
        Gtk::Application::create(argc, argv,
                                 "group54.moduLounge");

    // Create window, set size and border width
    Gtk::Window window;
    window.set_default_size(400, 400);
    window.set_border_width(30);

    // Load master CSS (automatically applied to all children module)
    auto css = Gtk::CssProvider::create();
    if (not css->load_from_path("src/main.css"))
    {
        std::cerr << "Failed to load main css\n";
        std::exit(1);
    }
    window.get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Create grid to house all the Modules/Frames
    Gtk::Grid grid;
    grid.set_halign(Gtk::ALIGN_CENTER);

    /*  This is how you add a module:
            1. Create the Module
            2. Show() the Frame that contains the actual thigns in the module
            3. Add the frame to the main grid
    */

    Wizard wizard = Wizard();
    wizard.userSetup();
    wizard.placeModules();
    std::vector<std::unique_ptr<Module>> modules = move(wizard.getModules());

    if (!modules.empty())
    {
        for (std::unique_ptr<Module> &i : modules)
        {
            i->populateModule();
            grid.attach(i->frame, i->getX(), i->getY(), 1, 1);
        }

        /* Once everything all the Boxes, Buttons, etc have been created and linked,
        we add the Grid to the Window and show all children */
        window.add(grid);
        window.show_all_children();

        return app->run(window);
    }
    return 0;
}
