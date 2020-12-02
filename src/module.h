#ifndef MODULE_H
#define MODULE_H

#include <gtkmm.h>

/**
 * Module class to create an empty module with name, width and height,
 * as well as a Gtk::Box that can hold child widgets. Serves as a base
 * for all modules. 
 * 
 * @author Caio C. Coelho <ccoelho6@uwo.ca>
 * @class Module
 * @brief The Module interface that all Modules inherit from.
*/
class Module
{
protected:
    int width, height;
    std::string name;
    Gtk::Box box;

public:
    /**
    * Main constructor. Inherits from Module and initializes the stock prices. 
    *  
    * @param name name of the module and frame in which it lives
    * @param width min requested width for the module
    * @param height min requested height for the module
    * @brief Main constructor
    */
    Module(std::string name, int width, int height);

    /**
    * Main destructor.
    * @brief Main destructor
    */
    virtual ~Module() = 0;

    /**
    * Returns the width of the module. 
    *  
    * @return int corresponding to the module's width
    * @brief Returns width of the module.
    */
    int getWidth();

    /**
    * Returns the height of the module. 
    *  
    * @return int corresponding to the module's height
    * @brief Returns height of the module.
    */
    int getHeight();

    /**
    * Returns the name of the module. 
    *  
    * @return string corresponding to the module's name
    * @brief Returns name of the module.
    */
    std::string getName();

    /**
    * Virtual method to pupolate the Gtk screen/UI with whatever the Module
    * wants to display
    *  
    * @brief abstract function to display the module's widgets on the screen.
    */
    virtual void populateModule() = 0;

    Gtk::Frame frame;
};

#endif //MODULE_H