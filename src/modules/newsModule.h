#ifndef NEWSMODULE_H
#define NEWSMODULE_H
#include <stdio.h>
#include<iostream>
#include <curl/curl.h>
#include <string>
#include <cstring>
#include<jsoncpp/json/json.h>
#include<exception>
#include <gtkmm.h>
#include "../module.h"

class NewsModule : public Module
{
private:
    struct jsonNews
    {
        public:
        std::string description;
        std::string date;
        std::string source;
        std::string title;
        std::string content;
    };
    struct newsData
    {
        public:
        char *data;
        size_t size;
    };
    static size_t saveData(void *contents, size_t size, size_t nmemb, void *userp);
    std::string formatFilter(std::string filter);
    void saveJson(jsonNews *jNews, newsData news);
    jsonNews newsToDisplay;

public:
    // Use parent constructor. You may not need to customize this constructor at all.
    // New widgets (buttons, text, etc) are supposed to be created in populateModule(), not the constructor.
    NewsModule(std::string name, int width, int height) : Module(name, width, height){};

    void populateModule(); // Add new stuff to the module.

    // Signal handlers:
    void on_button_clicked();

    // Member widgets:
    Gtk::Button button, button2; // All of your widgets need to be data members
};

#endif // NEWSMODULE_H
