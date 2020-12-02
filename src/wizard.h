#include <iostream>
#include <vector>
#include <memory>
#include "module.h"

#ifndef WIZARD_H
#define WIZARD_H

class Wizard {
    private:
        std::vector<std::unique_ptr<Module>> created_modules;
        void setupModule(const std::string& module, int setup, std::vector<std::string>& module_names);
        static std::unique_ptr<Module> setupWeather(std::string name);
        static std::unique_ptr<Module> setupCalendar(std::string name);
        static std::unique_ptr<Module> setupNews(std::string name);
        static std::unique_ptr<Module> setupSport(std::string name);
        static std::unique_ptr<Module> setupStocks(std::string name);
        static std::unique_ptr<Module> setupMusic(std::string name);
        void removeModule(const std::string& module);
    public:
        void userSetup();
        std::vector<std::unique_ptr<Module>> & getModules();
};

#endif //WIZARD_H
