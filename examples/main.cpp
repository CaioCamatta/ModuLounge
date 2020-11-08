#include <gtkmm.h>
#include "module.h"

int main(int argc, char *argv[])
{
    auto app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");

    Gtk::Window window;
    window.set_default_size(200, 200);
    MyModule module(&window);

    return app->run(window);
}