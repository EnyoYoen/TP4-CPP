#ifndef DATETIME_H
#define DATETIME_H

#include <cstddef>
#include <string>
#include <unordered_map>

using namespace std;

typedef long long ll;

class DateTime {
public:
    DateTime(const string& rfc2822);

    ll secondsBetween(const DateTime& dt) const;

    int getHour() const { return hour; }

    friend ostream& operator<<(ostream& os, const DateTime& dt);

private:
    ll year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    const unordered_map<string, int> monthStrToInt = {
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
};


#endif // DATETIME_H