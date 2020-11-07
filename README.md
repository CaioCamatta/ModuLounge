# ModuLounge

The ModuLounge is a Raspberry Pi application to turn a screen into a smart-ish lounge TV that displays weather information, news, stocks, cooking recipes, and plays music. All these modules can be arranged on the screen, and no user input is required while the program is running. However, to set up the program, the user will be presented with a step-by-step configuration Wizard to customize which modules are shown on TV, specify their behaviours, and pick other settings (e.g. what song/playlist is to be played). The live data is obtained through multiple different APIs.

## Installation
First, Install GTKMM

    apt-get install libgtkmm-3.0-dev

Then, compile the code 

    `g++ helloworld.cpp helloworld.h main.cpp -o ModuLounge `pkg-config --cflags --libs gtkmm-3.0`

To run the app, 

    ./ModuLounge

