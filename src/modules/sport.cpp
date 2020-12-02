#include <gtkmm.h>
#include <curl/curl.h>
#include <json/json.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "sport.h"
#include <math.h>

void displayArticles(Json::Value articles);
Json::Value getSportsNews(std::string sport);
static std::size_t writeFunction(char *ptr, std::size_t size, std::size_t num, char* out);
Sport::~Sport(){};
std::string format(std::string des, int runLength);

void Sport::initializeSports(std::string sport){
   // if(sport != "basketball")
    this->articles = getSportsNews(sport); //retrieve the articles  
}

/* Creates custom widgets (like buttons) for the custom module.
This basically expands upon the parent Module. */
void Sport::populateModule(){
    std::cout << "Start populating sport Module" << std::endl;

    int index1, index2, index3;

    index1 = 0;
    index2 = ceil(this->articles["articles"].size()/2);
    index3 = this->articles["articles"].size()-1;

    std::string des1 = this->articles["articles"][index1]["description"].asString();
    std::string des2 = this->articles["articles"][index2]["description"].asString();
    std::string des3 = this->articles["articles"][index3]["description"].asString();

    std::string title1 = this->articles["articles"][index1]["title"].asString();
    std::string title2 = this->articles["articles"][index2]["title"].asString();
    std::string title3 = this->articles["articles"][index3]["title"].asString();

    des1 = format(des1, 100);
    des2 = format(des2, 100);
    des3 = format(des3, 100);

    title1 = format(title1, 80);
    title2 = format(title2, 80);
    title3 = format(title3, 80);


    this->vbox = Gtk::VBox();
    this->frame.remove();
    this->frame.add(this->vbox);

    this->display1 = Gtk::Label("Title: " + title1 + "\n"
    "Written by " + this->articles["articles"][index1]["author"].asString() + "\n" +
    "From: " + this->articles["articles"][index1]["source"]["name"].asString() + "\n" +
    "Published at: " + this->articles["articles"][index1]["publishedAt"].asString() + "\n" +
    "Description: " + des1 + "\n");

    this->display2 = Gtk::Label("Title: " + title2 + "\n"
    "Written by " + this->articles["articles"][index2]["author"].asString() + "\n" +
    "From: " + this->articles["articles"][index2]["source"]["name"].asString() + "\n" +
    "Published at: " + this->articles["articles"][index2]["publishedAt"].asString() + "\n" +
    "Description: " + des2 + "\n");

    this->display3 = Gtk::Label("Title: " + title3 + "\n"
    "Written by " + this->articles["articles"][index3]["author"].asString() + "\n" +
    "From: " + this->articles["articles"][index3]["source"]["name"].asString() + "\n" +
    "Published at: " + this->articles["articles"][index3]["publishedAt"].asString() + "\n" +
    "Description: " + des3 + "\n");
    
    this->display1.set_justify(Gtk::JUSTIFY_LEFT);
    this->display2.set_justify(Gtk::JUSTIFY_LEFT);
    this->display3.set_justify(Gtk::JUSTIFY_LEFT);


    this->vbox.pack_start(this->display1, Gtk::PACK_SHRINK,0);
    this->vbox.pack_start(this->display2, Gtk::PACK_SHRINK,0);
    this->vbox.pack_start(this->display3, Gtk::PACK_SHRINK,0);

    std::cout << "Finished populating custom Module" << std::endl;
}

void displayArticles(Json::Value articles){
    int size = articles["articles"].size();
    for(int x = 0; x < size; x++){
        std::cout << articles["articles"][x]["title"].asString() << "\n";
        std::cout << "Written by " << articles["articles"][x]["author"].asString() << " from " << articles["articles"][x]["source"]["name"].asString() << "\n";
        std::cout << "Published on " << articles["articles"][x]["publishedAt"].asString() << "\n";
        std::cout << articles["articles"][x]["description"].asString() << "\n";
        std::cout << "\n";
    }
}

Json::Value getSportsNews(std::string sport){

    for(int x = 0; sport[x]; x++){
        if(sport[x] == ' '){
            sport[x] = '+';
        }
    }

    const std::string APIKEY = "78572ce08bad450c9a68185c8b7fc9c5";
    const std::string URL = "http://newsapi.org/v2/everything?q=" + sport + "&language=en&sortBy=publishedAt&apiKey=" + APIKEY; //url automatically only takes articles from todays date

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
           
        std::stringstream response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);    //response is written to a response stream, which is sent to the write function

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
       
        Json::Value data;
        Json::CharReaderBuilder reader;
        std::string errs;
        
        if(Json::parseFromStream(reader, response_string, &data, &errs)){
            return data;
        }
        throw std::string("No articles could be found for your input. Please enter a more recognizable team or sport.");
    } 
}

static std::size_t writeFunction(char *ptr, std::size_t size, std::size_t num, char* out) {
    std::string data (ptr, (std::size_t) size * num); //create a string of the data using ptr (which i believe is a pointer to the response stream)
    *((std::stringstream*) out) << data;
    return size * num;
}

std::string format(std::string des, int runLength){
    int charCount = 0;
    for(int i = 0; des[i]; i++){
        charCount++;
        if(charCount > runLength && des[i] == ' '){
            std::string temp1 = des.substr(0, i);
            std::string temp2 = des.substr(i+1);

            std::cout << temp1 << "\n";
            std::cout << temp2 << "\n";

            des = temp1 + "\n" + temp2;
            charCount = 0;
        }
    }

    return des;
}
