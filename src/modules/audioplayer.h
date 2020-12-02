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
        Gtk::Label curSong;
    public:
        Audioplayer(std::string name, int x, int y) : Module(name,x,y) {};
        ~Audioplayer();

        void populateModule();

        void on_button_clicked();

        void audioThread();

        Gtk::Button button, button2;
};


#endif