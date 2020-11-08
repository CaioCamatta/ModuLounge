#include <gtkmm.h>
#include "sampleModule.h"
#include "module.h"

int main(int argc, char *argv[])
{
    auto app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");

    Gtk::Window window;
    window.set_default_size(400, 400);
    window.set_border_width(30);

    /*  This is how you add a module 
            1. Create the Module
            2. Show() the Frame that contains the actual thigns in the module
            3. Add the frame to the main grid 
    */
    SampleModule module("Sample Module",100, 100);
    module.populateModule();
    window.add(module.frame);

    window.show_all_children();

    return app->run(window);
}