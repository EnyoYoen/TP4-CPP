//---------- Réalisation de la classe <Request> (fichier Request.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <sstream>
#include <exception>

//------------------------------------------------------ Include personnel
#include "Request.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Request::~Request()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Request>" << endl;
#endif
} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs

istream &operator>>(istream &is, Request &req)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la surcharge de l'operateur >>" << endl;
    #endif
    // Permet de parser les informations pour une ligne de log
    getline(is, req.infos.ip, ' ');
    if (req.infos.ip.empty())
        throw runtime_error("Invalid IP");

    getline(is, req.infos.userLogName, ' ');
    if (req.infos.userLogName.empty())
        throw runtime_error("Invalid User log name");

    getline(is, req.infos.userName, ' ');
    if (req.infos.userName.empty())
        throw runtime_error("Invalid User name");

    is.ignore(1); // Ignore le crochet ouvrant

    string dtStr;
    getline(is, dtStr, ']');
    if (!DateTime::isFullDateTimeCorrect(dtStr))
        throw runtime_error("Invalid CLF timestamp");
    istringstream dateStream(dtStr);
    dateStream >> req.infos.dateTime;

    is.ignore(2); // Ignore l'espace et le guillemet

    getline(is, req.infos.method, ' ');
    if (req.infos.method.empty())
        throw runtime_error("Invalid Request Method");

    getline(is, req.resource, ' ');
    if (req.resource.empty())
        throw runtime_error("Invalid Resource");

    getline(is, req.infos.protocol, '"');
    if (req.infos.protocol.empty())
        throw runtime_error("Invalid Protocol");

    is.ignore(1); // Ignore l'espace

    is >> req.infos.statusCode;
    if (req.infos.statusCode < 100 || req.infos.statusCode >= 600)
        throw runtime_error("Invalid status code");

    is.ignore(1); // Ignore l'espace

    string size;
    getline(is, size, ' ');
    if (size == "-" || size.empty())
    {
        size = "0";
    }
    req.infos.size = stoi(size);
    if (req.infos.size < 0)
        throw runtime_error("Invalid Size");

    is.ignore(1); // Ignore l'espace et le guillemet

    getline(is, req.infos.referer, '"');
    if (req.infos.referer.empty())
        throw runtime_error("Invalid Referer");

    is.ignore(2); // Ignore l'espace et le guillemet

    getline(is, req.infos.userAgent, '"');

    return is;
} //----- Fin de Méthode

ostream &operator<<(ostream &os, const Request &req)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel a la surcharge de l'operateur <<" << endl;
    #endif
    // Permet d'afficher les informations récupérée
    // Utilisée pour le debug
    os << req.infos.ip << " " << req.infos.userLogName << " " << req.infos.userName << " " << req.infos.dateTime << "] \"" << req.infos.method << " " << req.resource << " " << req.infos.protocol << "\" \"" << req.infos.userAgent << "\"";

    return os;
} //----- Fin de Méthode