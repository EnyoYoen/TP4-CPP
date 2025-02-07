//---------- Interface de la classe <DateTime> (fichier DateTime.h) ----------------
#ifndef DATETIME_H
#define DATETIME_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <cstddef>
#include <string>
#include <unordered_map>

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef long long ll;
typedef short i16;


//------------------------------------------------------------------------
// Rôle de la classe <DateTime>
// Cette classe permet de représenter une date et une heure, a partir d'une date au format RFC2822.
//------------------------------------------------------------------------


class DateTime
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
    DateTime() 
     // Mode d'emploi :
    //
    // Contrat :
    //
    {};

    virtual ~DateTime() 
     // Mode d'emploi :
    //
    // Contrat :
    //
    {};

//-------------------------------------------- Autres méthodes publiques
    ll secondsBetween(const DateTime &dt) const;
    // Mode d'emploi :
    //  calcule le nombre de secondes écoulées entre l'instance actuelle de la 
    //  classe DateTime et un autre objet DateTime passé en paramètre
    // Contrat :
    //

    int getHour() const 
    // Mode d'emploi :
    //  Cette méthode renvoie l'heure (au format 24 heures) de l'objet DateTime actuel
    // Contrat :
    //
    { return hour; }
    

    static bool isDateTimeCorrect(const string &clf);
    // Mode d'emploi :
    //  vérifie si une chaîne de caractères (représentant une date et une heure) est valide
    // Contrat :
    //

    static bool isFullDateTimeCorrect(const string &clf);
    // Mode d'emploi :
    //  vérifie si une chaîne de caractères est valide selon le format CLF avec une timezone
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    friend istream &operator>>(istream &is, DateTime &dt);
    // Mode d'emploi :
    //
    // Contrat :
    //

    friend ostream &operator<<(ostream &os, const DateTime &dt);
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Attributs privés
    ll year;
    i16 month;
    i16 day;
    i16 hour;
    i16 minute;
    i16 second;

    static const unordered_map<string, i16> monthStrToInt;
};

//-------------------------------- Autres définitions dépendantes de <DateTime>

#endif // DATETIME_H