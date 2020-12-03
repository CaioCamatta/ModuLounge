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
    /**
     * @brief Set the calendar info and other class variables
     * Take the current time and find the month, date, and year. Calculate the day of the week which the
     * first day of the month falls on, and calculate the number of days in the month.
     * @param province The province or territory to check for stat holidays
     */
    void initializeCalendar(std::string province);

    /**
     * @brief Find the holidays based on the province
     * Go through all the statutory holidays in the country, and add the date and name for each in the province in the current month.
     * Some dates are calculated as the holidays are not linked to a number-date, but a weekday of the month.
     * @return A vector of all the holidays for the month in the specified province
     */
    std::map<int, std::string> getHolidays();

    std::string province;
    int month;
    int first;
    int length;
    int current_date;
    int year;
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

    /**
     * @brief Destructor.
     * Destroy the instance of the module
     */
    ~Calendar();

    /**
     * @brief Create the UI of the module.
     * Called after all the modules are configured, this function will draw out the information to be seen.
     * This function uses GTK elements to display text which includes the month and year, and lists the dates and names
     * of the month's holidays. It will also draw a grid used as the calendar itself which is dated, and highlights the current date
     * along with marking the holidays. If the month spans over 5 weeks (> 5 rows), then some cells of the calendar will contain
     * multiple dates
     */
    void populateModule();
};


#endif //CALENDAR_H
