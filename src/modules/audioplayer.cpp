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
    std::thread audioThread(&Audioplayer::startMusic, this);
    audioThread.detach();
}

void Audioplayer::startMusic(){

          DIR *dir;
          dirent *pdir;
          char buf[PATH_MAX];
          
          //this->curSong = Gtk::Label();
          getcwd(buf, sizeof(buf));
          
          string path = "/src/modules/audioFolder/" + this->genre + "/";
          const char * folder = path.c_str();
  
          strcat(buf, folder);
          
          dir = opendir(buf);
          while ((pdir = readdir(dir)) != NULL){
            strcat(buf,pdir->d_name);

            this->curSong.set_markup(pdir->d_name);

            const char *songfile = buf;
            playmusic(songfile);

            getcwd(buf, sizeof(buf));
            strcat(buf, folder);
          }

          closedir(dir);
  
}


Audioplayer:: ~Audioplayer(){

}

int Audioplayer::playmusic(const char *song)
{
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

    //if(argc < 2)
       // exit(0);

    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    /* open the file and get the decoding format */
    mpg123_open(mh, song);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        ao_play(dev, (char *) buffer, done);

    /* clean up */
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

    Audioplayer::audioThread();
    //this->box = Gtk::VBox();
    this->curSong = Gtk::Label();
    this->curSong.set_max_width_chars(40);
    this->curSong.set_line_wrap(true);

    this->box.pack_start(this->curSong,Gtk::PACK_SHRINK,0);
    this->box.set_size_request(250,100);

}