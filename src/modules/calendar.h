#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <map>
#include "../module.h"

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
        Calendar(const std::string& province, std::string name, int x, int y) : Module(name, x ,y) { initializeCalendar(province); };
        ~Calendar();
        void populateModule(); // Add new stuff to the module.
};


#endif //CALENDAR_H
