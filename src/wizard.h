#include <iostream>
#include <vector>
#include <memory>
#include "module.h"
#include "modules/weather.h"
//#include "calendar.h"

#ifndef CPP_WORKSPACE_WIZARD_H
#define CPP_WORKSPACE_WIZARD_H

class Wizard {
    private:
        std::vector<std::unique_ptr<Module>> created_modules;
        void setupModule(const std::string& module, int setup, std::vector<std::string>& module_names);
        static std::unique_ptr<Module> setupWeather(std::string name);
        static std::unique_ptr<Module> setupNews(std::string name);
        //static Calendar setupCalendar(std::string name);
        void removeModule(const std::string& module);
    public:
        void userSetup();
        std::vector<std::unique_ptr<Module>> & getModules();
};

#endif //CPP_WORKSPACE_WIZARD_H
