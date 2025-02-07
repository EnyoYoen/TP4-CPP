//---------- Interface (fichier Request.h) ----------------
#ifndef REQUEST_H
#define REQUEST_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DateTime.h"


//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle du fichier (Request.h)
// Ce fichier contient deux classes permettant de stocker les données des requetes.
// La struct Infos permet d'encapsuler toutes les informations.
// La classe Request contient deux surcharges d'opérateurs pour la sérialisation et la désérialisation des requetes.
//------------------------------------------------------------------------

//---------- Interface de la classe publique <Infos> (fichier Request.h) ----------------
struct Infos {

//-------------------------------------------- Constructeurs - destructeur
	Infos() {}
	// Mode d'emploi :
    //
    // Contrat :
    //

	Infos(const string& ip, const string& userLogName, const string& userName,
		  const string& dateTime, const string& method, const string& protocol, 
		  int statusCode, int size, const string& referer, const string& userAgent)
		: ip(ip), userLogName(userLogName), userName(userName), 
		  method(method), protocol(protocol), statusCode(statusCode), 
		  size(size), referer(referer), userAgent(userAgent) {}
	// Mode d'emploi :
    // Ce constructeur permet de créer une nouvelle structure Infos à partir des informations passées en paramètre
    // Contrat :
    //
	
	virtual ~Infos() {}
	// Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs prubliques
	string ip;
	string userLogName;
	string userName;
	DateTime dateTime;
	string method;
	string protocol;
	int statusCode;
	int size;
	string referer;
	string userAgent;
};


//---------- Interface de la classe <Request> (fichier Request.h) ----------------
class Request {

//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
	Request() {}
	// Mode d'emploi :
    //
    // Contrat :
    //

	Request(const string& ip, const string& userLogName, const string& userName, 
			const string& dateTime, const string& method, const string& resource, 
			const string& protocol, int statusCode, int size, const string& referer, 
			const string& userAgent)
		: resource(resource), infos(ip, userLogName, userName, dateTime, method, protocol, statusCode, size, referer, userAgent) {}
	// Mode d'emploi (constructeur de copie):
    // Ce constructeur permet de créer une nouvelle requête à partir des informations passées en paramètre
    // Contrat :
    //
	
	virtual ~Request();
	// Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

	friend ostream& operator<<(ostream& os, const Request& abonne);
	// Mode d'emploi :
    //
    // Contrat :
    //
	
	friend istream& operator>>(istream& is, Request& abonne);
	// Mode d'emploi :
    //
    // Contrat :
    //

	friend class Graph;
	friend class Infos;

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Attributs privées
	string resource;
	Infos infos;
};

//-------------------------------- Autres définitions dépendantes

#endif // REQUEST_H