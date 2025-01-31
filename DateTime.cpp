#include "DateTime.h"

#include <sstream>
#include <iostream>

const unordered_map<string, i16> DateTime::monthStrToInt = {
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
    ll monthDiff = this->month - dt.month;
    ll dayDiff = this->day - dt.day;
    ll hourDiff = this->hour - dt.hour;
    ll minuteDiff = this->minute - dt.minute;
    ll secondDiff = this->second - dt.second;

    return yearDiff * 31536000 + monthDiff * 2592000 + dayDiff * 86400 + hourDiff * 3600 + minuteDiff * 60 + secondDiff;
}

bool isDigit(char c) {
    return isdigit(static_cast<unsigned char>(c));
}

bool DateTime::isDateTimeCorrect(const string& clf) {
    // Vérifie si la chaîne est au format CLF

    if (clf.size() != 20) return false;

    if (!isDigit(clf[0]) || !isDigit(clf[1])) return false;
    if (clf[2] != '/') return false;

    string monthStr = clf.substr(3, 3);
    if (monthStrToInt.find(monthStr) == monthStrToInt.end()) return false;
    if (clf[6] != '/') return false;

    if (!isDigit(clf[7]) || !isDigit(clf[8]) || !isDigit(clf[9]) || !isDigit(clf[10])) return false;
    if (clf[11] != ':') return false;

    if (!isDigit(clf[12]) || !isDigit(clf[13])) return false;
    if (clf[14] != ':') return false;

    if (!isDigit(clf[15]) || !isDigit(clf[16])) return false;
    if (clf[17] != ':') return false;

    if (!isDigit(clf[18]) || !isDigit(clf[19])) return false;

    return true;
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