#ifndef UI_H
#define UI_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>

class UI : public Gtk::Window
{
public:
  UI();
  virtual ~UI();

protected:

  // Signal handlers:
  // Our new improved on_button_clicked(). (see below)
  void on_button_clicked(Glib::ustring data);

  // Child widgets:
  Gtk::Box m_box1;
  Gtk::Box m_box2;
  Gtk::Button m_button1;
  Gtk::Button m_button2;
  Gtk::Grid m_grid;
  Gtk::Frame m_Frame;
};

#endif // UI_H