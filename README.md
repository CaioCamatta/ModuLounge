# ModuLounge

The ModuLounge is a Raspberry Pi application to turn a screen into a smart-ish lounge TV that displays weather information, news, stocks, cooking recipes, and plays music. All these modules can be arranged on the screen, and no user input is required while the program is running. However, to set up the program, the user will be presented with a step-by-step configuration Wizard to customize which modules are shown on TV, specify their behaviours, and pick other settings (e.g. what song/playlist is to be played). The live data is obtained through multiple different APIs.

## Installation & Execution
First, Install GTKMM

    apt-get install libgtkmm-3.0-dev

Then, compile the code 

    `g++ helloworld.cpp helloworld.h main.cpp -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0`

To run the app, use

    ./ModuLounge

Alternatively, you can use `make` (preferred):

    make
    ./ModuLounge

## Docs
Graphical Interface (GTK):
- Hello World example: https://www.gtk.org/docs/getting-started/hello-world/

- Hello World example with explanations: https://developer.gnome.org/gtkmm-tutorial/stable/sec-helloworld.html.en

- GTKMM Docs: https://www.gtkmm.org/en/documentation.shtml


### Modules & the UI
This is the structure of the UI
- One `Window`
    - Contains one `Grid`
        - Which contains multiple `Frame`s. Each `Frame` is a Module.
            - Each `Frame` contains one `Box`
                - Each `Box` contains any number of other components, like `Button`s, `Label`s, etc. 