#include "audioplayer.h"

#include <filesystem>
#include <iostream>
#include "RtAudio.h"
using namespace std;

string curSong;
struct dirent *files;

void Audioplayer::startMusic(){
    DIR *folder = opendir("audiosource");
    
    while ((files = readdir (dir)) != NULL) {
        playSound(files->d_name);
    }
}

bool playSound(string songfile){
    RtAudio *song;
    int streamID;
    int buffersize = 256;
    int sampleHertz = 48000;

    FILE * inputSong = fopen(songfile,"rb");

    song = new RtAudio(&streamdID, 0,2,0,0, inputSong, &sampleHertz, &buffersize, 4);
    song->startStream();

    int count =0;
    while(count < 48000){

        songfile->tickStream(streamID);
        count+= buffersize;
    }
    
    songfile->stopStream(streamID);
    return true;
}

Audioplayer::Audioplayer(){

}

Audioplayer::~Audioplayer(){

}

void Audioplayer::populateModule(){
    //put some indication that music is playing
}

void Audioplayer::on_button_clicked(){

}

string Audioplayer::getCurrentSong(){
    return curSong;
}