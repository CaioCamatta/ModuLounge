#include <iostream>
#include <ctime>
#include "calendar.h"
#include "../module.h"
using namespace std;

string province;
int month;
int first;

string days_names[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Set basic month information and retrieve holidays
void Calendar::initializeCalendar(string province) {
    this->province = province;
    time_t now = time(0);
    tm *local_now = localtime(&now);
    int year = local_now->tm_year;
    month = local_now->tm_mon;
    int day_of_week = local_now->tm_wday;
    int date = local_now->tm_mday;
    first = (day_of_week - date + 1) % 7;
    first = first < 0 ? first + 7 : first;
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
    map<int, string> holidays = getHolidays();
    cout << "Day of first: " << days_names[first] << ", days in month: " << length << endl;
    for (auto i : holidays) {
        cout << i.first << ": " << i.second << endl;
    }
}

Calendar::~Calendar() {

}

//  Based on the province or territory (in Canada) get the holidays for that month
map<int, string> Calendar::getHolidays() {
    map<int, string> holidays;

    int area;

    // give the specified province/territory a integer value
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
                holidays.insert(pair<int, string>(first > 1 ? 16 - first : 9 - first, "Labour Day"));
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

void Calendar::populateModule()
{
    std::cout << "Start populating custom Module" << std::endl;

    // Create a button, with label "Press Me"
    this->button = Gtk::Button("Button");

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    this->button.signal_clicked().connect(sigc::mem_fun(*this,
                                                        &Calendar::on_button_clicked));

    // Add Button to our Box (the Box holds all the widgets of this Module)
    // Shrink Widget to its size, add 0 padding
    this->box.pack_start(button, Gtk::PACK_SHRINK,0);

    // Create a second button to demonstrate how multiple widgets can be added to Box
    this->button2 = Gtk::Button("Press Me 2");
    this->button2.signal_clicked().connect(sigc::mem_fun(*this,
                                                         &Calendar::on_button_clicked));
    this->box.pack_start(button2);

    std::cout << "Finished populating custom Module" << std::endl;
}

void Calendar::on_button_clicked()
{
    std::cout << "Button was pressed." << std::endl;
}