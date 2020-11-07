// ex3/window.cc
#include "window.h"
MyWindow::MyWindow() : paned_{Gtk::Orientation::ORIENTATION_VERTICAL}
{
    set_title("Example 3");     // Sets the window title.
    set_default_size(500, 200); // Set default size, width and height, in pixels.
    set_border_width(50);
    add(paned_);
    paned_.add1(frame1_);
    paned_.add2(frame2_);
    frame1_.set_label("Gtk::Frame 1 Widget"); // set the frames label
    frame2_.set_label("Gtk::Frame 2 Widget");
    frame1_.set_label_align(0.0, 0.25);
    frame2_.set_label_align(1.0);
    show_all_children();
}
MyWindow::~MyWindow() {}