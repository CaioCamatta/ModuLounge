#ifndef SPORT_H
#define SPORT_H

#include <gtkmm.h>
#include <jsoncpp/json/json.h>
#include "../module.h"

/**
 * @author Caleb Sutherland
 * @brief Implements a subclass of module called sport. Responsible for handling the sports news module.
 * Detailed Description: This class handles retreiving the sports news, getting it into the module and formatting it to fit in the proper sized box. It has a gtkmm frame, * * with a box inside containing at most three labels (which are the articles). The number of labels may vary depending on how big we want the box to be.
 * Note: Comments for each function (besides constructor) will be in the sport.cpp file
 */
class Sport : public Module{
    private:
        // struct article that holds all labels for an article to be displayed (labels are text widgets to be displayed)
        struct article
        {
            public:
            Gtk::Label title;
            Gtk::Label author;
            Gtk::Label source;
            Gtk::Label published;
            Gtk::Label description;
        };

        /**
        * @brief initializeSports is the first method called from the constructor, handles set up of the sport module prior to populating it
        * Detailed Description: This function calls all the necessary methods to retrieve and format the articles information to be displayed. 
        * It can also be called to refresh the module after a certain time period.
        * @param refresh: indicates if the call is a refresh of the data or the initial call
        * @return nothing 
        */
        void initializeSports(int refresh);

        /**
        * @brief getSportsNews handles calling the api being used to get news articles
        * Detailed Description: This function calls all the necessary methods to retrieve and format the articles information to be displayed. 
        * It can also be called to refresh the module after a certain time period.
        */       
        Json::Value getSportsNews();


        /**
         * @brief refresher creates a thread to run in the background and automatically refresh the sport module to display fresh articles.
         * Detailed description: the thread runs a loop with a set time to sleep, after the time is up it will call
         * initializeSports with a 1 as the parameter to indicate it is a refresh call. This allows initialize sports to
         * take care of refreshing the articles being displayed currently.
         * @return data: the JSON of the sports articles
         */
        void refresher();

        /**
         * @brief formatDate takes in a date and substrings it so that only the day month year are in the text
         * Detailed Description: loops through a string and finds the first letters, takes everything up to that letter so that the date only contains what
         * we need and not extra data (looks cleaner). Uses a pointer so that it doesn't need to return anything (pass by reference)
         * @param date: date to be formatted, it is a pointer so it is passed by reference and the function doesnt need to return anything.
         */
        void formatDate(std::string *date);

        // widgets to hold an article
        article art1;
        //main box to hold everything
        Gtk::VBox vboxMain;  
        // the sport/team specified by the user 
        std::string sport;
        // A json array of articles that are retreived from api
        Json::Value articles;

    public:
        /**
         * @brief constructor calls initialize sport, which handles getting the information prior to displaying the module.
         * Detailed description: I feel as though a constructor is self explanatory
         * @param sport: the keyword entered by the user to be searched by the api
         * @param name: name of module
         * @param width: width of module
         * @param height: height of module
         */
        Sport(const std::string& sport, std::string name, int width, int height) : Module(name, width, height){
            this->sport = sport;
            initializeSports(0);
        };

        /**
         * @brief deconstructor to free memory used by sport modules
         * Detailed description: used to free memory for sport module objects
         */
        ~Sport();

        /**
         * @brief populateModule is called to add created labels of text to the main box for the sport module, allowing it to be displayed in the app.
         * Detailed description: populate module adds and aligns everything properly in a vertical box inside the sport module. Anything inside the vertical box
         * will be displayed, so populate module is actually populating the module for when the application runs.
         */
        void populateModule();  

        /**
         * @brief WriteFunction simply handles the return of the libcurl, it is necessary for the libcurl to work, but we don't use it for anything else
         * Detailed Description: It is necessary for the libcurl to work, it takes in the response_string and turns it into a stringstream output. 
         * @param ptr: the response stream
         * @param size: the size of the string stream
         * @param num: number of streams
         * @param out: the output stream
         * @return size of the output stream
         */
        static std::size_t writeFunction(char *ptr, std::size_t size, std::size_t num, char* out);    
};

#endif