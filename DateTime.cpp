#include "DateTime.h"

#include <sstream>
#include <iostream>

const unordered_map<string, int> DateTime::monthStrToInt = {
    {"Jan", 1},
    {"Feb", 2},
    {"Mar", 3},
    {"Apr", 4},
    {"May", 5},
    {"Jun", 6},
    {"Jul", 7},
    {"Aug", 8},
    {"Sep", 9},
    {"Oct", 10},
    {"Nov", 11},
    {"Dec", 12}
};

ll DateTime::secondsBetween(const DateTime& dt) const {
	// Retourne le nombre de secondes entre deux dates
    ll yearDiff = this->year - dt.year;
    int monthDiff = this->month - dt.month;
    int dayDiff = this->day - dt.day;
    int hourDiff = this->hour - dt.hour;
    int minuteDiff = this->minute - dt.minute;
    int secondDiff = this->second - dt.second;

    return yearDiff * 31536000 + monthDiff * 2592000 + dayDiff * 86400 + hourDiff * 3600 + minuteDiff * 60 + secondDiff;
}

istream& operator>>(istream& is, DateTime& dt) {
	// Permet de parser une date au format RFC2822
    is >> dt.day;
    is.ignore(1); // Ignore the slash
    string monthStr;
    getline(is, monthStr, '/');
    if (dt.monthStrToInt.find(monthStr) == dt.monthStrToInt.end()) {
        dt.month = 0;
    } else {
        dt.month = dt.monthStrToInt.at(monthStr);
    }
    is.ignore(1); // Ignore the slash
    is >> dt.year;
    is.ignore(1); // Ignore the colon
    is >> dt.hour;
    is.ignore(1); // Ignore the colon
    is >> dt.minute;
    is.ignore(1); // Ignore the colon
    is >> dt.second;

    return is;
}

ostream& operator<<(ostream& os, const DateTime& dt) {
	// Permet d'afficher une date
	// Utilisée pour le debug
    os << dt.day << "/" << dt.month << "/" << dt.year << ":" << dt.hour << ":" << dt.minute << ":" << dt.second;

    return os;
}