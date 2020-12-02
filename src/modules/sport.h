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
        void initializeSports(std::string sport);
        std::string format(std::string des, int runLength);
        void displayArticles(Json::Value articles);
        Json::Value getSportsNews(std::string sport);
        // the sport/team specified by the user 
        std::string sport;
        // A json array of articles that are retreived from api
        Json::Value articles;

    public:
        /**
         * @brief constructor calls initialize sport, which handles getting the information prior to displaying the module.
         * Detailed description: I feel as though a constructor is self explanatory
         */
        Sport(const std::string& sport, std::string name, int width, int height) : Module(name, width, height){
            this->sport = sport;
            initializeSports(sport);
        };

        ~Sport();

        void populateModule();

        void refresher(std::string sport);
        void refreshArticles(std::string sport);

        // widgets to display articles inside the frame 
        Gtk::Label display1, display2, display3;
        Gtk::VBox vboxMain;        
};

#endif