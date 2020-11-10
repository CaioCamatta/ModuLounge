#include "sport.h"
#include <gtkmm.h>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>

Sport::~Sport(){}
void initializeSports(std::string sport);
void displayArticles(Json::Value articles);
Json::Value getSportsNews(std::string sport);
static std::size_t writeFunction(char *ptr, std::size_t size, std::size_t num, char* out);

/* Creates custom widgets (like buttons) for the custom module.
This basically expands upon the parent Module. */
void Sport::populateModule()
{
    std::cout << "Start populating sport Module" << std::endl;

    // // Create a button, with label "Press Me"
    // this->button = Gtk::Button("Button");

    // // When the button receives the "clicked" signal, it will call the
    // // on_button_clicked() method defined below.
    // this->button.signal_clicked().connect(sigc::mem_fun(*this,
    //                                                     &SampleModule::on_button_clicked));

    // // Add Button to our Box (the Box holds all the widgets of this Module)
    // // Shrink Widget to its size, add 0 padding
    // this->box.pack_start(button, Gtk::PACK_SHRINK,0);

    // // Create a second button to demonstrate how multiple widgets can be added to Box
    // this->button2 = Gtk::Button("Press Me 2");
    // this->button2.signal_clicked().connect(sigc::mem_fun(*this,
    //                                                      &SampleModule::on_button_clicked));
    // this->box.pack_start(button2);

    std::cout << "Finished populating custom Module" << std::endl;
}

void Sport::on_button_clicked(){
    std::cout << "Button was pressed." << std::endl;
}

void Sport::initializeSports(std::string sport){
    Json::Value data = getSportsNews(sport); //retrieve the articles
    displayArticles(data);                   //display the articles
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
        throw std::string("The data could not be retrieved.");
    } 
}

static std::size_t writeFunction(char *ptr, std::size_t size, std::size_t num, char* out) {
    std::string data (ptr, (std::size_t) size * num); //create a string of the data using ptr (which i believe is a pointer to the response stream)
    *((std::stringstream*) out) << data;
    return size * num;
}