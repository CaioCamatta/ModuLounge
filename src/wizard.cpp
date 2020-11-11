#include <iostream>
#include <vector>
#include <cctype>
#include <memory>
#include "wizard.h"
#include "module.h"
#include "modules/weather.h"
#include "modules/calendar.h"
#include "modules/newsModule.h"
using namespace std;

vector<unique_ptr<Module>> created_modules;

int setupModule(string module, int setup, vector<string>& module_names);
unique_ptr<Module> setupWeather(string name);
unique_ptr<Module> setupCalendar(string name);
void removeModule(const string& module);

string lowercase(string& str) { transform(str.begin(), str.end(), str.begin(), ::tolower); return str;}

/* Requests input from user specifying the module they would like to add
 * Does this until user enters 'done' or 'exit'
 * Also allows for other actions such as 'help' and 'remove'
 */
void Wizard::userSetup() {
    vector<string> module_names = {"weather", "calendar", "news"};
    bool done = false;
    bool exit = false;

    cout << endl;
    cout << "Welcome to the ModuLounge Setup Wizard" << endl
    << "Enter the module(s) you would like to display:" << endl
    << "(other commands: 'help' 'done' 'exit')" << endl;

    while (!done) {
        string input;

        cout << "-> ";
        cin.clear();
        fflush(stdin);
        while (getline(cin, input)) {
            if (input.empty()) {
                cout << "-> ";
            } else {
                break;
            }
        }
        lowercase(input);

        // Check input
        if (input == "weather") {
            setupModule("weather", 1, module_names);
        } else if (input == "calendar") {
            setupModule("calendar", 2, module_names);
        } else if (input == "news") {
            setupModule("news", 3, module_names);
        } else if (input == "exit") {
            exit = true;
            done = true;
        } else if (input == "done") { // End the wizard to continue the program
            done = true;
        } else if (input == "show") { // List all the added modules
            cout << "\t" << created_modules.size() << " elements" << endl;
            for (unique_ptr<Module>& x: created_modules) {
                cout << "\t- " << x->getName() << endl;
            }
        } else if (input.substr(0, input.find(' ')) == "remove" || input.substr(0, input.find(' ')) == "rm") { // Remove a specified module
            if (input.find(' ') != string::npos) {
                string module_to_remove = input.substr(input.find(' ')+1, input.length() + 1);
                try {
                    removeModule(module_to_remove);
                    module_names.push_back(module_to_remove);
                    cout << "Successfully removed " << module_to_remove << endl;
                } catch (string& e) {
                    cout << e << endl;
                }
            } else {
                cout << "Please specify the module (e.g. 'rm weather')" << endl;
            }
        } else if (input == "help") { // List all actions and all remaining modules that can be added
            cout << "\tEnter one of the following module names to create a module" << endl;
            for (const auto & module_name : module_names) {
                cout << "\t- " << module_name << endl;
            }
            cout << "\tType 'show' to display the modules which you have added" << endl
            << "\tType 'done' when you have finished adding modules" << endl
            << "\tType 'exit' if you would like to abandon the wizard" << endl
            << "\tType 'rm [module]' to remove a specified module" << endl;
        } else {
            cout << "INVALID INPUT" << endl;
        }
    }
    if (exit) { // Remove added modules if user wishes to stop program
        created_modules.clear();
        cout << "Exiting" << endl << endl;
    } else if (created_modules.empty()) {
        cout << "No modules, exiting" << endl << endl;
    }
}

// Setup the specified module by calling its specific setup function, adding the resulting Module to the vector
void Wizard::setupModule(const string& module, int setup, vector<string>& module_names) {
    try {
        if (find(module_names.begin(), module_names.end(), module) != module_names.end()) {
            cout << "Creating " << module << " module" << endl;
            switch (setup) {
                case 1:
                    created_modules.emplace_back(setupWeather(module));
                    break;
                case 2:
                    created_modules.emplace_back(setupCalendar(module));
                case 3:
                    created_modules.emplace_back(setupNews(module));
                    break;
                default:
                    break;
            }
            module_names.erase(find(module_names.begin(), module_names.end(), module));
        } else {
            cout << "Module already added" << endl;
        }
    } catch (string &e) {
        cout << e << endl;
    }
}

// Setup the weather module by taking some user input and creating the module
unique_ptr<Module> Wizard::setupWeather(string name) {
    string city;
    cout << "Enter the city (optional: add a country code, e.g. 'London, CA'): ";
    getline(cin, city);
    return unique_ptr<Module>(new Weather(lowercase(city), name, 100, 50));
}

// Setup the calendar module by taking some user input and creating the module
unique_ptr<Module> Wizard::setupCalendar(string name) {
    string prov;
    cout << "Enter the province/territory: ";
    getline(cin, prov);
    return unique_ptr<Module>(new Calendar(lowercase(prov), name, 100, 100));
}

unique_ptr<Module> Wizard::setupNews(string name) {
    return unique_ptr<Module>(new NewsModule(name, 100, 50));
}

// Accessor for the vector of all created modules
vector<unique_ptr<Module>> & Wizard::getModules() {
    return created_modules;
}

// Removes a specified module from the vector of created modules if it is contained
void Wizard::removeModule(const string& module) {
    auto it = find_if(created_modules.begin(), created_modules.end(), [&module](const unique_ptr<Module>& obj) {return obj->getName() == module;});
    if(it != created_modules.end()) {
        created_modules.erase(it);
    } else {
        throw string("Unknown module");
    }
}
