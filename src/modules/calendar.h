#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <map>
#include "../module.h"

/**
 * @author Jack Hillier
 * @brief Calculate the calendar details and display it along with holidays
 * This class takes the current date and calculate what the calendar table will look like.
 * A province/territory will be specified and will be used to find the statutory holidays which differ among provinces/territories.
 * The calendar will be displayed along with a listing of the holidays in the month (which are also marked on the calendar).
 */
class Calendar : public Module {
    private:
        std::string province;
        int month;
        int first;
        int length;
        int current_date;
        int year;

        void initializeCalendar(std::string province);
        std::map<int, std::string> getHolidays();
    public:
        /**
         * @brief Constructor.
         * Create the instance and call for the initialization.
         * @param province The specified province or territory
         * @param name The name of the module
         * @param x The x-coordinate
         * @param y The y-coordinate
         */
        Calendar(const std::string& province, std::string name, int x, int y) : Module(name, x ,y) { initializeCalendar(province); };
        ~Calendar();
        void populateModule();
};


#endif //CALENDAR_H
