#ifndef DATETIME_H
#define DATETIME_H

#include <cstddef>
#include <string>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef short i16;

/*
Cette classe permet de représenter une date et une heure, a partir d'une date au format RFC2822.
*/

class DateTime {
public:
    DateTime() {};

    ll secondsBetween(const DateTime& dt) const;

    int getHour() const { return hour; }

    static bool isDateTimeCorrect(const string& clf);

    friend istream& operator>>(istream& is, DateTime& dt);
    friend ostream& operator<<(ostream& os, const DateTime& dt);

private:
    ll year;
    i16 month;
    i16 day;
    i16 hour;
    i16 minute;
    i16 second;

    static const unordered_map<string, i16> monthStrToInt;
};


#endif // DATETIME_H