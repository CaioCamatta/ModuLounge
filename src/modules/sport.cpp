#include <gtkmm.h>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <thread>
#include "sport.h"
#include <math.h>

// Destructor definition
Sport::~Sport(){};
static std::size_t writeFunction(char *ptr, std::size_t size, std::size_t num, char* out);

/**
 * @brief Initialize sports setts 
 * Detailed description: I feel as though a constructor is self explanatory
 */
void Sport::initializeSports(std::string sport, int refresh){
   
    this->articles = Sport::getSportsNews(sport); //retrieve the articles 

    if(refresh == 0){
        this->display1 = Gtk::Label();
        this->display2 = Gtk::Label();
        this->display3 = Gtk::Label();
    }

    if(this->articles["articles"].size() == 0){
        this->display1.set_markup("<span size='large'><b>No Articles Could Be Found for this keyword!</b></span> \n");  
    }
    else{
        int index1, index2, index3;
        //select three difference articles at random using an index number
        if(this->articles["articles"].size() >= 1){
            index1 = rand() % this->articles["articles"].size();
            index2 = rand() % this->articles["articles"].size();
            while(index2 == index1 && this->articles["articles"].size() >=2){
                index2 = rand() % this->articles["articles"].size();
            }
            index3 = rand() % this->articles["articles"].size();
            while(index3 == index2 || index3 == index1 && this->articles["articles"].size() >=3){
                index3 = rand() % this->articles["articles"].size();
            }
        }
        std::string des1 = this->articles["articles"][index1]["description"].asString();
        std::string des2 = this->articles["articles"][index2]["description"].asString();
        std::string des3 = this->articles["articles"][index3]["description"].asString();

        std::string title1 = this->articles["articles"][index1]["title"].asString();
        std::string title2 = this->articles["articles"][index2]["title"].asString();
        std::string title3 = this->articles["articles"][index3]["title"].asString();

        std::string author1 = this->articles["articles"][index1]["author"].asString();
        std::string author2 = this->articles["articles"][index2]["author"].asString();
        std::string author3 = this->articles["articles"][index3]["author"].asString();

        std::string published1 = this->articles["articles"][index1]["publishedAt"].asString();
        std::string published2 = this->articles["articles"][index2]["publishedAt"].asString();
        std::string published3 = this->articles["articles"][index3]["publishedAt"].asString();

        des1 = format(des1, 100);
        des2 = format(des2, 100);
        des3 = format(des3, 100);

        title1 = format(title1, 70);
        title2 = format(title2, 70);
        title3 = format(title3, 70);

        author1 = format(author1, 100);  
        author2 = format(author2, 100);   
        author3 = format(author3, 100);

        published1 = format(published1, 100);   
        published2 = format(published2, 100);   
        published3 = format(published3, 100);   

        this->display1.set_markup("<span size='large'><b>\n" + title1 + "</b></span> \n---------------------------\n"
        "<b>Written by</b> \n" + author1 + "\n" +
        "<b>From</b> \n" + this->articles["articles"][index1]["source"]["name"].asString() + "\n" +
        "<b>Published at</b> \n" + published1 + "\n" + "<b>Description</b> \n" +
        des1 + "\n");

        this->display2.set_markup("<span size='large'><b>\n" + title2 + "</b></span> \n---------------------------\n"
        "<b>Written by</b> \n" + author2 + "\n" +
        "<b>From</b> \n" + this->articles["articles"][index2]["source"]["name"].asString() + "\n" +
        "<b>Published at</b> \n" + published2 + "\n" + "<b>Description</b> \n" +
        des2 + "\n");

        this->display3.set_markup("<span size='large'><b>\n" + title3 + "</b></span> \n---------------------------\n"
        "<b>Written by</b> \n" + author3 + "\n" +
        "<b>From</b> \n" + this->articles["articles"][index3]["source"]["name"].asString() + "\n" +
        "<b>Published at</b> \n" + published3 + "\n" + "<b>Description</b> \n" +
        des3 + "\n");   
    }
}

/* Creates custom widgets (like buttons) for the custom module.
This basically expands upon the parent Module. */
void Sport::populateModule(){
    std::cout << "Start populating sport Module" << std::endl;



    //initialize vertical box to display articles on top of one another
    this->vboxMain = Gtk::VBox();

    //remove the box currently in the frame that was inherited
    this->frame.remove();
    //add the new box to the frame
    this->frame.add(this->vboxMain);

    this->display1.set_halign(Gtk::ALIGN_START);
    this->display2.set_halign(Gtk::ALIGN_START);
    this->display3.set_halign(Gtk::ALIGN_START);

    this->vboxMain.pack_start(this->display1, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->display2, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->display3, Gtk::PACK_SHRINK,0);

    std::thread sportThread(&Sport::refresher, this, this->sport);
    sportThread.detach();

    std::cout << "Finished populating custom Module" << std::endl;
}


Json::Value Sport::getSportsNews(std::string sport){
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

std::string Sport::format(std::string des, int runLength){
    int charCount = 0;
    for(int i = 0; i < des.length(); i++){
        charCount++;
        if(charCount > runLength){
            if(des[i] == ' '){
                std::string temp1 = des.substr(0, i+1);
                std::string temp2 = des.substr(i+1);
                des = temp1 + "\n" + temp2;
            }
            else{
                std::string temp1 = des.substr(0, i);
                std::string temp2 = des.substr(i+1);
                des = temp1 + "-\n" + temp2;
            }
            charCount = 0;
        }
    }
    return des;
}

void Sport::refresher(std::string sport){
    while(true){
        std::this_thread::sleep_for (std::chrono::seconds(20));
        Sport::initializeSports(sport, 1);
    }
}

