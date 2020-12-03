#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <iostream>
#include "../module.h"

/**
 * @author Daniel Wakefield + Caleb Sutherland
 * @brief Implements a subclass of module called Audioplayer. Responsible for handling the playing of music while the application runs.
 * Detailed Description: This class takes a name of one of the music folders and plays the playlist of mp3 files located in that folder. 
 * The music is played in a separate process so that it doesn't interfere with anything else running.
 */
class Audioplayer: public Module{

    private:
        /**
        * @brief startMusic opens a directory given the proper file path and passes each song in the directory to the playMusic function to be played.
        * Detailed description: contains a loop that goes through a directory over and over again passing the songs (mp3's) in the directory to
        * the play music function one at a time. startMusic handles getting the proper types and paths so that playMusic can just take a song and play it.
        */
        void startMusic();
        /**
        * @brief playMusic handles playing the song that is passed to it
        * Detailed description: take a pointer to the song in memory and uses <ao/ao.h> and <mpg123.h> to play it.
        * @param song: pointer to the song that is getting played
        * @return integer to signal end of playing
        */
        int playmusic(const char *song);

        // returns the current song
        std::string getCurrentSong();

        // used to display the current song being played in the module frame
        Gtk::Label curSong;

        Gtk::Image image1;
        Gtk::Image image2;
        std::string icon;
        // stores what genre the user wants played from the setup wizard
        std::string genre;
    public:
        /**
        * @brief constructor that creates audio player objects and sets the genre to what the user inputted
        * Detailed description: self explanatory
        * @param genre: genre of music to be played
        * @param name: name of module
        * @param x: width of module
        * @param y: height of module
        */
        Audioplayer(const std::string& genre, std::string name, int x, int y) : Module(name,x,y) {this->genre = genre;};
        ~Audioplayer();

        /**
        * @brief populates the module with the name of song being played currently, updates everytime the song changes
        * Detailed description: populates the module with the name of the song being played from the current playlist, adds the label to the box being displayed in the frame 
        * for the module
        */
        void populateModule();

        /**
        * @brief creates a thread so that the music can play in the background without interupting the other modules
        * Detailed description:thread is what initializes all the music, or else all other modules would have to wait for every song to be played before executing themselves.
        * the thread allows the music name to be updated in the module while its being displayed and play music in the background.
        */
        void audioThread();
};


#endif