#include "ui.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
  // The Wizard must be executed before the GTK UI is created
  // TODO: Add Wizard (Wizard.cpp, Wizard.h) here

  auto app = Gtk::Application::create(argc, argv, "group54.moduLounge");

  UI ui;

  //Shows the window and returns when it is closed.
  return app->run(ui);
}