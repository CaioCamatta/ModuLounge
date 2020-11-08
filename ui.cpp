#include "ui.h"
#include <iostream>

UI::UI()
: m_button1("Button 1"),
  m_button2("Button 2")
{
  // Set the title of our window.
  set_title("Hello Buttons!");
  // Set the border width of the window.
  set_border_width(50);

  // Now when the button is clicked, we call the "on_button_clicked" function
  // with a pointer to "button 1" as it's argument
  m_button1.signal_clicked().connect(sigc::bind<Glib::ustring>(
      sigc::mem_fun(*this, &UI::on_button_clicked), "button 1"));

  // instead of gtk_container_add, we pack this button into the invisible
  // box, which has been packed into the window.
  // note that the pack_start default arguments are Gtk::EXPAND | Gtk::FILL, 0
  m_box1.pack_start(m_button1);
  m_box1.set_border_width(20);


  /* Set the frames label */
  m_Frame.set_label("Frame Widget");

  /* Set the style of the frame */
  m_Frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
  m_Frame.set_border_width(10);

  m_Frame.add(m_box1);

  // call the same signal handler with a different argument,
  // passing a pointer to "button 2" instead.
  m_button2.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
      sigc::mem_fun(*this, &UI::on_button_clicked), "button 2"));

  m_box2.pack_start(m_button2);

  add(m_grid);

  m_grid.add(m_Frame);
  m_grid.add(m_box2);

  show_all_children();
}

UI::~UI()
{
}

// Our new improved signal handler.  The data passed to this method is
// printed to stdout.
void UI::on_button_clicked(Glib::ustring data)
{
  std::cout << "Hello World - " << data << " was pressed" << std::endl;
}
