#include <iostream>
#include <vector>
#include <memory>
#include "module.h"

#ifndef WIZARD_H
#define WIZARD_H

/**
 * @author Jack Hillier
 * @brief Create the modules through the command line.
 * Prompt the user with a command-line-interface where they can enter the modules they'd like to add.
 * Once the modules have been created, prompt the user to select the positioning of the modules.
 */
class Wizard {
private:
    /**
     * @brief Create a module.
     * Add a module to the vector that is created by one of the module setup methods. Check first if
     * the module has been created already via the module_names vector
     * @param module The name of the module to set up
     * @param setup Denotes the module you wish to set up
     * @param module_names A list of the not-yet created modules
     */
    void setupModule(const std::string& module, int setup, std::vector<std::string>& module_names);

    /**
     * @brief Setup the Weather Module.
     * Prompt the user for any information needed in the creation of the module, then return Module instance.
     * @param name The name of the module
     * @return The Module instance pointer
     */
    static std::unique_ptr<Module> setupWeather(std::string name);

    /**
     * @brief Setup the Calendar Module.
     * Prompt the user for any information needed in the creation of the module, then return Module instance.
     * @param name The name of the module
     * @return The Module instance pointer
     */
    static std::unique_ptr<Module> setupCalendar(std::string name);

    /**
     * @brief Setup the News Module.
     * Prompt the user for any information needed in the creation of the module, then return Module instance.
     * @param name The name of the module
     * @return The Module instance pointer
     */
    static std::unique_ptr<Module> setupNews(std::string name);

    /**
     * @brief Setup the Sport Module.
     * Prompt the user for any information needed in the creation of the module, then return Module instance.
     * @param name The name of the module
     * @return The Module instance pointer
     */
    static std::unique_ptr<Module> setupSport(std::string name);

    /**
     * @brief Setup the Stocks Module.
     * Prompt the user for any information needed in the creation of the module, then return Module instance.
     * @param name The name of the module
     * @return The Module instance pointer
     */
    static std::unique_ptr<Module> setupStocks(std::string name);
    /**
     * @brief Setup the Music Module.
     * Prompt the user for any information needed in the creation of the module, then return Module instance.
     * @param name The name of the module
     * @return The Module instance pointer
     */
    static std::unique_ptr<Module> setupMusic(std::string name);

    /**
     * @brief Remove the specified module.
     * Take the name of the Module to remove, then remove it from the vector of created modules
     * @param module The name of the specified module
     */
    void removeModule(const std::string& module);

    std::vector<std::unique_ptr<Module>> created_modules;
public:
    /**
     * @brief Create the command-line-interface.
     * Allow the user to enter their desired modules along with ask for help, list their modules,
     * remove a module, or exit the application.
     */
    void userSetup();

    /**
     * @brief Setup the placement of the modules.
     * Go through each of the modules and prompt the user for the desired location of each.
     */
    void placeModules();

    /**
     * @brief Getter for modules
     * Get the vector of all the created modules.
     * @return The vector of all the created modules
     */
    std::vector<std::unique_ptr<Module>> & getModules();
};

#endif //WIZARD_H
