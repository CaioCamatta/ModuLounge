#include <iostream>
#include <gtkmm.h>
#include <vector>
#include <memory>
#include "modules/sampleModule.h"
#include "modules/weather.h"
#include "module.h"
#include "wizard.h"
#include "modules/newsModule.h"

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

    // Create grid to house all the Modules/Frames
    Gtk::Grid grid;

    /*  This is how you add a module:
            1. Create the Module
            2. Show() the Frame that contains the actual thigns in the module
            3. Add the frame to the main grid
    */

    /*std::vector<std::unique_ptr<Module>> modules;

    modules.emplace_back(new SampleModule("Sample Module", 100, 100));
    modules.emplace_back(new Weather("Toronto", "Sample Module 2", 100, 50));*/

    Wizard wizard = Wizard();
    wizard.userSetup();
    std::vector<std::unique_ptr<Module>> modules = move(wizard.getModules());

    if (!modules.empty()) {
        for (std::unique_ptr <Module> &i : modules) {
            i->populateModule();
            grid.add(i->frame);
        }

        /* Once everything all the Boxes, Buttons, etc have been created and linked,
        we add the Grid to the Window and show all children */
        window.add(grid);
        window.show_all_children();

        return app->run(window);
    }
    return 0;
}
