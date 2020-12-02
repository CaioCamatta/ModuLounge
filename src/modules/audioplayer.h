#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "../module.h"
//#include <filesystem>
#include <iostream>

class Audioplayer: public Module{

    private:
        void startMusic();
        int playmusic(const char *song);
        std::string getCurrentSong();
        std::string curSong;
    public:
        Audioplayer(std::string name, int x, int y) : Module(name,x,y) {startMusic();};
        ~Audioplayer();

        void populateModule();

        void on_button_clicked();

        Gtk::Button button, button2;
};


#endif