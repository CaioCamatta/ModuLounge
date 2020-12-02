/** @file calendar.cpp */
#include <iostream>
#include <ctime>
#include <thread>
#include "calendar.h"
#include "../module.h"
using namespace std;

// Set basic month information and retrieve holidays
/**
 * @brief Set the calendar info and other class variables
 * Take the current time and find the month, date, and year. Calculate the day of the week which the
 * first day of the month falls on, and calculate the number of days in the month.
 * @param province The province or territory to check for stat holidays
 */
void Calendar::initializeCalendar(string province) {
    this->province = province;

    // Get the current time
    time_t now = time(0);
    tm *local_now = localtime(&now);

    // Find the details of the time
    this->year = local_now->tm_year + 1900;
    this->month = local_now->tm_mon;
    int day_of_week = local_now->tm_wday;
    this->current_date = local_now->tm_mday;

    // Calculate the day of the week which the first day falls on
    this->first = (day_of_week - current_date + 1) % 7;
    this->first = first < 0 ? first + 7 : first;

    // Calculate the length of the month
    int length;
    if (month == 1 && year % 4 == 0) {
        length = 29;
    } else if (month == 1) {
        length = 28;
    } else if (month <= 6 && month % 2 == 0) {
        length = 31;
    } else if (month <= 6) {
        length = 30;
    } else if (month % 2 == 0) {
        length = 30;
    } else {
        length = 31;
    }
    this->length = length;
}

/**
 * @brief Destructor.
 * Destroy the instance of the module
 */
Calendar::~Calendar() {

}

//  Based on the province or territory (in Canada) get the holidays for that month
/**
 * @brief Find the holidays based on the province
 * Go through all the statutory holidays in the country, and add the date and name for each in the province in the current month.
 * Some dates are calculated as the holidays are not linked to a number-date, but a weekday of the month.
 * @return A vector of all the holidays for the month in the specified province
 */
map<int, string> Calendar::getHolidays() {
    map<int, string> holidays;

    // Give the specified province/territory a integer value
    int area;
    if (province == "alberta" || province == "ab") {
        area = 1;
    } else if (province == "british columbia" || province == "bc") {
        area = 2;
    } else if (province == "manitoba" || province == "mb") {
        area = 3;
    } else if (province == "new brunswick" || province == "nb") {
        area = 4;
    } else if (province == "newfoundland" || province == "nl") {
        area = 5;
    } else if (province == "northwest territories" || province == "nt") {
        area = 6;
    } else if (province == "nova scotia" || province == "ns") {
        area = 7;
    } else if (province == "nunavut" || province == "nu") {
        area = 8;
    } else if (province == "ontario" || province == "on") {
        area = 9;
    } else if (province == "prince edward island" || province == "pei" || province == "pe") {
        area = 10;
    } else if (province == "quebec" || province == "qc") {
        area = 11;
    } else if (province == "saskatchewan" || province == "sk") {
        area = 12;
    } else if (province == "yukon territories" || province == "yukon" || province == "yt") {
        area = 13;
    } else {
        throw string("Invalid Province/Territory");
    }

    // Go through all the months and for each, go through all the holidays and add the ones which are applicable
    switch (month) {
        case 0: {
            holidays.insert(pair<int, string>(1, "New Year's Day"));
            return holidays;
        } case 1: {
            switch (area) {
                case 3:
                    holidays.insert(pair<int, string>(first > 1 ? 23 - first : 16 - first, "Louis Riel Day"));
                    break;
                case 10:
                    holidays.insert(pair<int, string>(first > 1 ? 23 - first : 16 - first, "Islander Day"));
                    break;
                case 1:
                case 2:
                case 4:
                case 9:
                case 12:
                    holidays.insert(pair<int, string>(first > 1 ? 23 - first : 16 - first, "Family Day"));
                    break;
                case 7:
                    holidays.insert(pair<int, string>(first > 1 ? 23 - first : 16 - first, "Heritage Day"));
                    break;
            }
            return holidays;
        } case 2: {
            holidays.insert(pair<int, string>(17, "Saint Patrick's Day"));
            return holidays;
        } case 3: {
            holidays.insert(pair<int, string>(first > 5 ? 13 - first : 6 - first, "Good Friday"));
            if (area == 10) {
                holidays.insert(pair<int, string>(first > 5 ? 16 - first : 9 - first, "Easter Monday"));
            }
            if (area == 5) {
                holidays.insert(pair<int, string>(23, "Saint George's Day"));
            }
            return holidays;
        } case 4: {
            int monday = first == 6 ? 30 : 23;
            if (area == 11) {
                holidays.insert(
                        pair<int, string>(first > 1 ? monday - first : monday - 7 - first, "National Patriot's Day"));
            } else {
                holidays.insert(pair<int, string>(first > 1 ? monday - first : monday - 7 - first, "Victoria Day"));
            }
            return holidays;
        } case 5: {
            if (area == 6 || area == 13) {
                holidays.insert(pair<int, string>(21, "National Aboriginal Day"));
            }
            if (area == 5 || area == 11 || area == 13) {
                holidays.insert(pair<int, string>(24, "National Holiday"));
            }
            return holidays;
        } case 6: {
            holidays.insert(pair<int, string>(1, "Canada Day"));
            if (area == 5) {
                holidays.insert(pair<int, string>(12, "Orangemen's Day"));
            }
            return holidays;
        } case 7: {
            switch (area) {
                case 1:
                case 13:
                    holidays.insert(pair<int, string>(first > 1 ? 9 - first : 2 - first, "Heritage Day"));
                    break;
                case 2:
                    holidays.insert(pair<int, string>(first > 1 ? 9 - first : 2 - first, "British Columbia Day"));
                    break;
                case 3:
                    holidays.insert(pair<int, string>(first > 1 ? 9 - first : 2 - first, "Saskatchewan Day"));
                    break;
                case 4:
                    holidays.insert(pair<int, string>(first > 1 ? 9 - first : 2 - first, "New Brunswick Day"));
                    break;
                case 5:
                case 6:
                case 8:
                case 9:
                case 12:
                    holidays.insert(pair<int, string>(first > 1 ? 9 - first : 2 - first, "Civic Holiday"));
                    break;
                case 7:
                    holidays.insert(pair<int, string>(first > 1 ? 9 - first : 2 - first, "Natal Day"));
                    break;
                case 10:
                    holidays.insert(pair<int, string>(first > 5 ? 27 - first : 20 - first, "Gold Cup Parade Day"));
                    break;
            }
            if (area == 13) {
                holidays.insert(pair<int, string>(first > 1 ? 23 - first : 16 - first, "Discovery Day"));
            }
            return holidays;
        } case 8: {
            holidays.insert(pair<int, string>(first > 1 ? 9 - first : 2 - first, "Labour Day"));
            return holidays;
        } case 9: {
            if (!(area == 4 || area == 5 || area == 7 || area == 10)) {
                holidays.insert(pair<int, string>(first > 1 ? 16 - first : 9 - first, "Thanksgiving"));
            }
            return holidays;
        } case 10: {
            if (!(area == 3 || area == 5 || area == 9 || area == 11)) {
                holidays.insert(pair<int, string>(11, "Remembrance Day"));
            } else if (area == 5) {
                holidays.insert(pair<int, string>(11, "Armistice Day"));
            }
            return holidays;
        } case 11: {
            holidays.insert(pair<int, string>(25, "Christmas Day"));
            if (area == 1 || area == 4 || area == 7 || area == 9 || area == 10) {
                holidays.insert(pair<int, string>(26, "Boxing Day"));
            }
            return holidays;
        } default: return holidays;
    }
}

/**
 * @brief Create the UI of the module.
 * Called after all the modules are configured, this function will draw out the information to be seen.
 * This function uses GTK elements to display text which includes the month and year, and lists the dates and names
 * of the month's holidays. It will also draw a grid used as the calendar itself which is dated, and highlights the current date
 * along with marking the holidays. If the month spans over 5 weeks (> 5 rows), then some cells of the calendar will contain
 * multiple dates
 */
void Calendar::populateModule()
{
    cout << "Start populating custom Module" << std::endl;

    string month_names[12] = {"January", "February", "March", "April", "May", "June", "July",
                       "August", "September", "October", "November", "December"};

    this->box.set_size_request(300,200); // Set module size

    Gtk::Grid* container = new Gtk::Grid(); // Grid for module layout

    // Create calendar
    Gtk::Grid* grid = new Gtk::Grid();
    grid->set_row_spacing(1);
    grid->set_column_spacing(1);

    map<int, std::string> holidays = getHolidays(); // Get the holidays

    // Create the title
    Gtk::Label* title = new Gtk::Label();
    title->set_markup("<span size='large'><b>" + month_names[this->month] + ", " + to_string(this->year) + "</b></span>");
    title->set_padding(0, 2);
    container->attach(*title,0,0,1,1);

    // Create each cell of the calendar
    int day = 1;
    for (int i = 0; day <= this->length && i < 5; i++) {
        for (int j = i == 0 ? this->first : 0; j < 7 && day <= this->length; j++) {
            if ((this->length >= 30 && day+7 == 30 && j == 0) || (this->length >= 31 && day+7 == 31 && (j == 0 || j == 1))) {
                // The cell is double-dated to abolish a sixth column

                Gtk::Box *cell = new Gtk::Box();
                Gtk::Label *date = new Gtk::Label();
                cell->set_size_request(25,20);

                // Create date label (upper left of cell)
                if (day == current_date || day+7 == current_date) {
                    if (day == current_date) {
                        date->set_markup("<span rise='1000' size='x-small'><b>" + to_string(day) +
                                         "</b></span>\n<span rise='1000' size='xx-small'>" + to_string(day+7) + "</span>");
                    } else {
                        date->set_markup("<span rise='1000' size='xx-small'>" + to_string(day) +
                                         "</span>\n<span rise='1000' size='x-small'><b>" + to_string(day+7) + "</b></span>");
                    }
                } else {
                    date->set_markup("<span rise='1000' size='xx-small'>" + to_string(day) + "\n" + to_string(day+7) + "</span>");
                }
                date->set_xalign(0.1);
                date->set_yalign(0.1);
                date->set_padding(0, 0);
                cell->pack_start(*date);

                // Create holiday label if applicable
                if (holidays.find(day) != holidays.end() || holidays.find(day+7) != holidays.end()) {
                    Gtk::Label *today = new Gtk::Label();
                    if (holidays.find(day+7) != holidays.end()) {
                        today->set_markup("<span rise='-1000' size='x-small' foreground='#FFB0B0'><b>" + holidays.find(day+7)->second.substr(0,1) + "</b></span>");
                    } else {
                        today->set_markup("<span rise='-1000' size='x-small' foreground='#FFB0B0'><b>" + holidays.find(day)->second.substr(0,1) + "</b></span>");
                    }
                    today->set_xalign(0.6);
                    today->set_yalign(0.9);
                    today->set_padding(0, 0);
                    cell->pack_end(*today);
                }

                // Highlight the cell if it represents the current date
                if (day == current_date || day+7 == current_date) {
                    cell->get_style_context()->add_class("calendar-cell-today");
                } else {
                    cell->get_style_context()->add_class("calendar-cell");
                }

                // Add the cell to the table
                grid->attach(*cell, j, i,1,1);
            } else {
                // Repeat the above without use of double-dated checking and labelling
                Gtk::Box *cell = new Gtk::Box();
                Gtk::Label *date = new Gtk::Label();
                if (day == current_date) {
                    date->set_markup("<span rise='1000' size='x-small'><b>" + to_string(day) + "</b></span>");
                } else {
                    date->set_markup("<span rise='1000' size='xx-small'>" + to_string(day) + "</span>");
                }
                if (holidays.find(day) != holidays.end()) {
                    Gtk::Label *today = new Gtk::Label();
                    today->set_markup("<span rise='-1000' size='x-small' foreground='#FFB0B0'><b>" + holidays.find(day)->second.substr(0,1) + "</b></span>");
                    today->set_xalign(0.6);
                    today->set_yalign(0.9);
                    today->set_padding(0, 0);
                    cell->pack_end(*today);
                }
                date->set_xalign(0.1);
                date->set_yalign(0.1);
                date->set_padding(0, 0);
                cell->pack_start(*date);
                cell->set_size_request(25,20);
                if (day == current_date) {
                    cell->get_style_context()->add_class("calendar-cell-today");
                } else {
                    cell->get_style_context()->add_class("calendar-cell");
                }
                grid->attach(*cell, j, i,1,1);
            }

            day++;
        }
    }
    container->attach(*grid,0,1,1,1);

    // Create holiday listing
    Gtk::Label* text = new Gtk::Label();
    string holiday_string = "";
    first = true;

    // Go through the holidays and add them to a string
    for (auto const& x : holidays)
    {
        if (!first) {
            holiday_string.append("\n");
        }
        first = false;
        holiday_string.append(to_string(x.first));
        if (x.first % 10 == 1 && (x.first > 20 || x.first < 10)) {
            holiday_string.append("<span rise='5000'>st</span>: ");
        } else if (x.first % 10 == 2 && (x.first > 20 || x.first < 10)) {
            holiday_string.append("<span rise='5000'>nd</span>: ");
        } else if (x.first % 10 == 2 && (x.first > 20 || x.first < 10)) {
            holiday_string.append("<span rise='5000'>rd</span>: ");
        } else {
            holiday_string.append("<span rise='5000' size='small'>th</span>: ");
        }
        holiday_string.append(x.second);
    }

    // Set the string as a label
    text->set_markup(holiday_string);
    text->set_xalign(0);
    text->set_yalign(1);
    text->set_padding(0, 5);

    // Add the label to the layout grid
    container->attach(*text,0,2,1,1);

    // Centre the layout grid
    container->set_halign(Gtk::ALIGN_CENTER);

    // Add the layout grid to the module
    this->box.pack_start(*container);

    cout << "Finished populating custom Module" << endl;
}