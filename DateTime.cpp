#include "DateTime.h"

#include <sstream>
#include <iostream>

DateTime::DateTime(const string& rfc2822) {
    istringstream is(rfc2822);
    is >> day;
    is.ignore(1); // Ignore the slash
    string monthStr;
    getline(is, monthStr, '/');
    if (monthStrToInt.find(monthStr) == monthStrToInt.end()) {
        month = 0;
    } else {
        month = monthStrToInt.at(monthStr);
    }
    is.ignore(1); // Ignore the slash
    is >> year;
    is.ignore(1); // Ignore the colon
    is >> hour;
    is.ignore(1); // Ignore the colon
    is >> minute;
    is.ignore(1); // Ignore the colon
    is >> second;
}

ll DateTime::secondsBetween(const DateTime& dt) const {
    ll yearDiff = this->year - dt.year;
    int monthDiff = this->month - dt.month;
    int dayDiff = this->day - dt.day;
    int hourDiff = this->hour - dt.hour;
    int minuteDiff = this->minute - dt.minute;
    int secondDiff = this->second - dt.second;

    return yearDiff * 31536000 + monthDiff * 2592000 + dayDiff * 86400 + hourDiff * 3600 + minuteDiff * 60 + secondDiff;
}

ostream& operator<<(ostream& os, const DateTime& dt) {
    os << dt.day << "/" << dt.month << "/" << dt.year << ":" << dt.hour << ":" << dt.minute << ":" << dt.second;

    return os;
}