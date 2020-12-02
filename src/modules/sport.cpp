#include <gtkmm.h>
#include <curl/curl.h>
#include <json/json.h>
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
void formatDate(std::string *date);

/**
 * @brief Initialize sports setts 
 * Detailed description: I feel as though a constructor is self explanatory
 */
void Sport::initializeSports(std::string sport, int refresh){
   
    this->articles = Sport::getSportsNews(sport); //retrieve the articles 

    if(refresh == 0){
        this->art1.title = Gtk::Label();
        this->art2.title = Gtk::Label();
        this->art3.title = Gtk::Label();

        this->art1.author = Gtk::Label();
        this->art2.author = Gtk::Label();
        this->art3.author = Gtk::Label();

        this->art1.source = Gtk::Label();
        this->art2.source = Gtk::Label();
        this->art3.source = Gtk::Label();

        this->art1.published = Gtk::Label();
        this->art2.published = Gtk::Label();
        this->art3.published = Gtk::Label();

        this->art1.description = Gtk::Label();
        this->art2.description = Gtk::Label();
        this->art3.description = Gtk::Label();  
    }

    if(this->articles["articles"].size() == 0){
        this->art1.title.set_markup("<span size='large'><b>No Articles Could Be Found for this keyword!</b></span> \n");  
    }
    else{
        int index1, index2, index3;
        //select three different articles at random using an index number
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

        std::string source1 = this->articles["articles"][index1]["source"]["name"].asString();
        std::string source2 = this->articles["articles"][index2]["source"]["name"].asString();
        std::string source3 = this->articles["articles"][index3]["source"]["name"].asString();

        std::string published1 = this->articles["articles"][index1]["publishedAt"].asString();
        std::string published2 = this->articles["articles"][index2]["publishedAt"].asString();
        std::string published3 = this->articles["articles"][index3]["publishedAt"].asString();

        formatDate(&published1);
        formatDate(&published2);
        formatDate(&published3);

        if(author1.length() == 0){
            author1 = "Author N/A";
        }
        if(author2.length() == 0){
            author2 = "Author N/A";
        }
        if(author3.length() == 0){
            author3 = "Author N/A";
        }
        
 
        this->art1.title.set_markup("<span size='large'><b>\n" + title1 + "</b></span>");
        this->art1.title.set_max_width_chars(60);
        this->art1.title.set_line_wrap(true);

        this->art1.author.set_markup("<i>\n" + author1 + "</i>");
        this->art1.author.set_max_width_chars(60);
        this->art1.author.set_line_wrap(true);

        this->art1.source.set_markup("----------------------\n" + source1);
        this->art1.source.set_max_width_chars(60); //could cause problem with styleing
        this->art1.source.set_line_wrap(true);

        this->art1.published.set_markup("----------------------\n"+ published1);
        this->art1.published.set_max_width_chars(60);
        this->art1.published.set_line_wrap(true);

        this->art1.description.set_markup("\n"+ des1);
        this->art1.description.set_max_width_chars(60);
        this->art1.description.set_line_wrap(true);

//second
        this->art2.title.set_markup("<span size='large'><b>\n" + title2 + "</b></span>");
        this->art2.title.set_max_width_chars(60);
        this->art2.title.set_line_wrap(true);

        this->art2.author.set_markup("<i>\n" + author2 + "</i>");
        this->art2.author.set_max_width_chars(60);
        this->art2.author.set_line_wrap(true);

        this->art2.source.set_markup("----------------------\n" + source2);
        this->art2.source.set_max_width_chars(60); //could cause problem with styleing
        this->art2.source.set_line_wrap(true);

        this->art2.published.set_markup("----------------------\n"+ published2);
        this->art2.published.set_max_width_chars(60);
        this->art2.published.set_line_wrap(true);

        this->art2.description.set_markup("\n"+ des2);
        this->art2.description.set_max_width_chars(60);
        this->art2.description.set_line_wrap(true);

//third
        this->art3.title.set_markup("<span size='large'><b>\n" + title3 + "</b></span>");
        this->art3.title.set_max_width_chars(60);
        this->art3.title.set_line_wrap(true);

        this->art3.author.set_markup("<i>\n" + author3 + "</i>");
        this->art3.author.set_max_width_chars(60);
        this->art3.author.set_line_wrap(true);

        this->art3.source.set_markup("----------------------\n" + source3);
        this->art3.source.set_max_width_chars(60); //could cause problem with styleing
        this->art3.source.set_line_wrap(true);

        this->art3.published.set_markup("----------------------\n"+ published3);
        this->art3.published.set_max_width_chars(60);
        this->art3.published.set_line_wrap(true);

        this->art3.description.set_markup("\n"+ des3);
        this->art3.description.set_max_width_chars(60);
        this->art3.description.set_line_wrap(true);
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

    this->art1.title.set_halign(Gtk::ALIGN_START);
    this->art1.author.set_halign(Gtk::ALIGN_START);
    this->art1.published.set_halign(Gtk::ALIGN_START);
    this->art1.description.set_halign(Gtk::ALIGN_START);
    this->art1.source.set_halign(Gtk::ALIGN_START);

    this->art2.title.set_halign(Gtk::ALIGN_START);
    this->art2.author.set_halign(Gtk::ALIGN_START);
    this->art2.published.set_halign(Gtk::ALIGN_START);
    this->art2.description.set_halign(Gtk::ALIGN_START);
    this->art2.source.set_halign(Gtk::ALIGN_START);

    this->art3.title.set_halign(Gtk::ALIGN_START);
    this->art3.author.set_halign(Gtk::ALIGN_START);
    this->art3.published.set_halign(Gtk::ALIGN_START);
    this->art3.description.set_halign(Gtk::ALIGN_START);
    this->art3.source.set_halign(Gtk::ALIGN_START);

    this->vboxMain.pack_start(this->art1.title, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art1.author, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art1.source, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art1.published, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art1.description, Gtk::PACK_SHRINK,0);

    this->vboxMain.pack_start(this->art2.title, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art2.author, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art2.source, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art2.published, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art2.description, Gtk::PACK_SHRINK,0);

    this->vboxMain.pack_start(this->art3.title, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art3.author, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art3.source, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art3.published, Gtk::PACK_SHRINK,0);
    this->vboxMain.pack_start(this->art3.description, Gtk::PACK_SHRINK,0);

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

void Sport::refresher(std::string sport){
    while(true){
        std::this_thread::sleep_for (std::chrono::seconds(20));
        Sport::initializeSports(sport, 1);
    }
}

void formatDate(std::string *date){
    if(date->length() != 0){
        std::string temp = *date;
        int i = 0;
        while((int) temp[i] < 65){
            i++;
        }
        *date = temp.substr(0, i);
    }
}

