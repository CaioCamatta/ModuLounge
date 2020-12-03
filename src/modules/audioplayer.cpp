#include <ao/ao.h>
#include <mpg123.h>
#include <iostream>
#include <thread>
#include <limits.h>
#include <unistd.h>
#include "audioplayer.h"
#include "dirent.h"

using namespace std;
#define BITS 8



struct dirent *files;

void Audioplayer::audioThread(){   
    // creates a thread  to play the audio in the background of all the other modules
    std::thread audioThread(&Audioplayer::startMusic, this);
    audioThread.detach();
}

void Audioplayer::startMusic(){
    // this while loop keeps the playlist repeating until the user closes the application
  while(true){
    
    DIR *dir; // opens a directory at a specified path
    dirent *pdir; // stores each file in a directory
    char buf[PATH_MAX]; // stores the specified path to a directory
    
    //gets the current working directory and stores it into buf
    getcwd(buf, sizeof(buf));
    
    // appends the continued path to the directory storing the mp3 files with the user's specified genre folder
    string path = "/src/modules/audioFolder/" + this->genre + "/";
    const char * folder = path.c_str();

    // concatenates the continued path to the current working directory to get a full path to the song files
    strcat(buf, folder);
    
    dir = opendir(buf);

    // will loop until there are no more files in the song file directory 
    while ((pdir = readdir(dir)) != NULL){
      strcat(buf,pdir->d_name);

      // sets the Label widget's text to the current song's file name to display in the UI
      string filename = pdir->d_name;
      this->curSong.set_markup("<b>" + filename + "</b>");
      // converts the full path into a const char * to be played in the playmusic function
      const char *songfile = buf;
      playmusic(songfile);

      // resets the path for the next file
      getcwd(buf, sizeof(buf));
      strcat(buf, folder);
    }

    closedir(dir);
  }
}


Audioplayer:: ~Audioplayer(){

}

int Audioplayer::playmusic(const char *song)
{
    // varaibles needed to decode and play mp3 files
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;


    // initializes the audio output driver and initializes the audio reader and decoder
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    // opens the file and get the decoding format, in this case, mp3 files
    mpg123_open(mh, song);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    // set the output format to get the total number of bits in the audio file and open the output device, which is the system's default output speaker 
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    // decode and play, looping through all the bits of the mp3 file by increments of the buffer until the song is done
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        ao_play(dev, (char *) buffer, done);

    // frees the allocated memory, closes the opened files, and decoders, then shuts down the audio player and the decoder
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();

    return 0;
}


void Audioplayer::populateModule(){

    std::cout << "Playing Playlist" << std::endl;

    Gtk::Grid* container = new Gtk::Grid();
    // when the module is created, create a new thread to play music in the background
    Audioplayer::audioThread();
    this->image1 = Gtk::Image(Gdk::Pixbuf::create_from_file("src/images/musicnote.png",20,20));
    this->image1.get_style_context()->add_class("icon");
    container->attach(this->image1,0,0,1,1);
    // Creates, styles, and outputs the song's file name to the UI
    this->curSong = Gtk::Label();
    this->curSong.set_max_width_chars(40);
    this->curSong.set_line_wrap(true);

    container->attach(this->curSong,0,1,1,1);
    container->set_halign(Gtk::ALIGN_CENTER);
    this->box.pack_start(*container);


}