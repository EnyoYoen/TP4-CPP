#ifndef DATETIME_H
#define DATETIME_H

#include <cstddef>
#include <string>
#include <unordered_map>

using namespace std;

typedef long long ll;

/*
Cette classe permet de représenter une date et une heure, a partir d'une date au format RFC2822.
*/

typedef char i8;

class DateTime {
public:
    DateTime() {};

    ll secondsBetween(const DateTime& dt) const;

    int getHour() const { return hour; }

    friend istream& operator>>(istream& is, DateTime& dt);
    friend ostream& operator<<(ostream& os, const DateTime& dt);

private:
    ll year;
    i8 month;
    i8 day;
    i8 hour;
    i8 minute;
    i8 second;

    static const unordered_map<string, i8> monthStrToInt;
};


#endif // DATETIME_H