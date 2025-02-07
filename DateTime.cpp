//---------- Réalisation de la classe <DateTime> (fichier DateTime.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <sstream>
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DateTime.h"


//------------------------------------------------------------- Constantes
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
    {"Dec", 12}};


//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

ll DateTime::secondsBetween(const DateTime &dt) const
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la methode secondsBetween";
    #endif

    // Retourne le nombre de secondes entre deux dates
    ll yearDiff = this->year - dt.year;
    ll monthDiff = this->month - dt.month;
    ll dayDiff = this->day - dt.day;
    ll hourDiff = this->hour - dt.hour;
    ll minuteDiff = this->minute - dt.minute;
    ll secondDiff = this->second - dt.second;

    return yearDiff * 31536000 + monthDiff * 2592000 + dayDiff * 86400 + hourDiff * 3600 + minuteDiff * 60 + secondDiff;
} //----- Fin de Méthode

bool isDigit(char c)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la methode isDigit";
    #endif

    return isdigit(static_cast<unsigned char>(c));
} //----- Fin de Méthode

bool isValidSecondsOrMinutes(char c1, char c2)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la methode isValidSecondsOrMinutes";
    #endif

    return isDigit(c1) && isDigit(c2) && ((c1 >= '0' && c1 <= '5') || (c1 == '6' && c2 == '0'));
} //----- Fin de Méthode

bool isValidHour(char c1, char c2)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la methode isValidHour";
    #endif

    return isDigit(c1) && isDigit(c2) && ((c1 >= '0' && c1 <= '2') || (c1 == '2' && c2 <= '3'));
} //----- Fin de Méthode

bool isDayCorrect(char c1, char c2)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la methode isDayCorrect";
    #endif

    return isDigit(c1) && isDigit(c2) && ((c1 >= '0' && c1 <= '3'));
} //----- Fin de Méthode

bool isYearCorrect(char c1, char c2, char c3, char c4)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la methode isYearCorrect";
    #endif
    return isDigit(c1) && isDigit(c2) && isDigit(c3) && isDigit(c4);
} //----- Fin de Méthode

bool DateTime::isDateTimeCorrect(const string &clf)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la methode isDateTimeCorrect";
    #endif

    // Vérifie si la chaîne est au format CLF (sans timezone)

    if (clf.size() != 20)
        return false;

    if (!isDayCorrect(clf[0], clf[1]))
        return false;
    if (clf[2] != '/')
        return false;

    string monthStr = clf.substr(3, 3);
    if (monthStrToInt.find(monthStr) == monthStrToInt.end())
        return false;
    if (clf[6] != '/')
        return false;

    if (!isYearCorrect(clf[7], clf[8], clf[9], clf[10]))
        return false;
    if (clf[11] != ':')
        return false;

    if (!isValidHour(clf[12], clf[13]))
        return false;
    if (clf[14] != ':')
        return false;

    if (!isValidSecondsOrMinutes(clf[15], clf[16]))
        return false;
    if (clf[17] != ':')
        return false;

    if (!isValidSecondsOrMinutes(clf[18], clf[19]))
        return false;

    return true;
} //----- Fin de Méthode

bool DateTime::isFullDateTimeCorrect(const string &clf)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la methode isFullDateTimeCorrect";
    #endif

    // Vérifie si la chaîne est au format CLF (avec timezone)

    if (clf.size() != 26)
        return false;

    if (!DateTime::isDateTimeCorrect(clf.substr(0, 20)))
        return false;

    if (clf[20] != ' ')
        return false;

    if (clf[21] != '-' && clf[21] != '+')
        return false;

    if (!isDigit(clf[22]) || !isDigit(clf[23]) || !isDigit(clf[24]) || !isDigit(clf[25]))
        return false;

    return true;
} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs
istream &operator>>(istream &is, DateTime &dt)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la surcharge de l'operateur >>";
    #endif

    // Permet de parser une date au format RFC2822
    is >> dt.day;
    is.ignore(1); // Ignore the slash
    string monthStr;
    getline(is, monthStr, '/');
    if (dt.monthStrToInt.find(monthStr) == dt.monthStrToInt.end())
    {
        dt.month = 0;
    }
    else
    {
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
} //----- Fin de Méthode

ostream &operator<<(ostream &os, const DateTime &dt)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la surcharge de l'operateur <<";
    #endif

    // Permet d'afficher une date
    // Utilisée pour le debug
    os << dt.day << "/" << dt.month << "/" << dt.year << ":" << dt.hour << ":" << dt.minute << ":" << dt.second;

    return os;
} //----- Fin de Méthode