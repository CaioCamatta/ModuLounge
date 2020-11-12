#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "../module.h"
//#include <filesystem>
#include <iostream>

class Audioplayer: public Audioplayer{

    private:
        void startMusic();
        std::string getCurrentSong();
        std::string curSong;
    public:
        Audioplayer(std::string songname, int x, int y) : Module(songname,x,y) {startMusic();};
        ~Audioplayer();

        void populateModule();

        void on_button_clicked();

        Gtk::Button button, button2;
};


#endif