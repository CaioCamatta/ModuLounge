# ModuLounge

The ModuLounge is a Raspberry Pi application to turn a screen into a smart-ish lounge TV that displays weather information, news, stocks, cooking recipes, and plays music. All these modules can be arranged on the screen, and no user input is required while the program is running. However, to set up the program, the user will be presented with a step-by-step configuration Wizard to customize which modules are shown on TV, specify their behaviours, and pick other settings (e.g. what song/playlist is to be played). The live data is obtained through multiple different APIs.

## Installation & Execution

Use Linux preferably.

First, Install GTKMM and other libraries required

    sudp apt-get install libgtkmm-3.0-dev
    sudo apt-get install libjsoncpp-dev
    sudo apt-get install libcurl4 libcurl4-openssl-dev -y
    sudo apt-get install libboost-dev

To run the app, use `make`:

    make
    ./ModuLounge

## Relevant Docs

**Important:** Before you start creating the UI for your Module, it's essential to understand the UI library we are using (`gtkmm`). Read these docs:

- [GTKMM Basics](https://developer.gnome.org/gtkmm-tutorial/stable/chapter-basics.html.en)

- [Hello World example](https://developer.gnome.org/gtkmm-tutorial/stable/sec-helloworld.html.en)

- [GTKMM Docs](https://www.gtkmm.org/en/documentation.shtml)

  - [Container Widgets (e.g. Boxes)](https://developer.gnome.org/gtkmm-tutorial/stable/chapter-container-widgets.html.en)
  - [Misc Widgets (e.g. text Labels)](https://developer.gnome.org/gtkmm-tutorial/stable/chapter-misc-widgets.html.en)

- [GTK CSS Properties](https://developer.gnome.org/gtk3/stable/chap-css-properties.html)

- [Pango Markup - Similar to HTML/CSS](https://developer.gnome.org/pygtk/stable/pango-markup-language.html)

## UI Structure

This is the structure of the UI

- One `Window`, with one `Grid` inside.
  - The `Grid` may contain multiple `Frame`s. A `Frame` represents a Module.
    - Each `Frame` contains one `Box`
      - Each `Box` contains any number of other widgets, like `Button`s, `Label`s, etc. Your widgets go in this `Box`.

What are Widgets?

- [Widgets](https://developer.gnome.org/gtkmm-tutorial/stable/sec-widgets-overview.html.en) are buttons, text boxes, etc. You will be using these, so take a looks at the ones avaiable (GTKMM Docs).

How do I create a module>

- Under `src/modules`, you will create `yourModule.cpp` and `yourModule.h`. Use the `sampleModule` as reference. All modules we create inherit from `Module`, which is the parent class that conveniently creates (and sets up) a `Frame` and `Box` to be used by the children modules. Your custom module needs to be instantiated and configured in `main.cpp` (again, use the sample module as reference).

## Adding CSS

`main.css` can be accessed by any widget in the entire application. Simple add your css class to `main.css`, e.g.

    .my-custom-css {color: red;}

Then add your class (`my-custom-css`) to your Widget, e.g.

    this->myWidget.get_style_context()->add_class("my-custom-css");

You can also create separate CSS files (e.g. `stock.css`) and use them in your module. There is an example of how to use a separate css file under `sampleModule.cpp`.

### An easier alternative (Pango)

Instead of using css, you can also use [Pango](https://developer.gnome.org/pygtk/stable/pango-markup-language.html), which is similar to HTML & CSS. It allows you to overwrite, for example the text of a `Label`, e.g.
Instead of

    this->currentTime = Gtk::Label("Test");
    this->currentTime.get_style_context()->add_class("italic"); // italic is defined in the css file

You could have

    this->currentTime = Gtk::Label();
    this->currentTime.set_markup("<i>New test</i>");

Where the later would be in italic.
