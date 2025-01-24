#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

#include "DateTime.h"

using namespace std;

/*
Ce fichier contient deux classes permettant de stocker les données des requetes.
La struct Infos permet d'encapsuler toutes les informations.
La classe Request contient deux surcharges d'opérateurs pour la sérialisation et la désérialisation des requetes.
*/

struct Infos {
	Infos() : dateTime(nullptr) {}
	Infos(const string& ip, const string& userLogName, const string& userName,
		  const string& dateTime, const string& method, const string& protocol, 
		  int statusCode, int size, const string& referer, const string& userAgent)
		: ip(ip), userLogName(userLogName), userName(userName), 
		  method(method), protocol(protocol), statusCode(statusCode), 
		  size(size), referer(referer), userAgent(userAgent) {
			this->dateTime = new DateTime(dateTime);
		  }

	string ip;
	string userLogName;
	string userName;
	DateTime *dateTime;
	string method;
	string protocol;
	int statusCode;
	int size;
	string referer;
	string userAgent;
};

class Request {
public:
	Request() {}
	Request(const string& ip, const string& userLogName, const string& userName, 
			const string& dateTime, const string& method, const string& resource, 
			const string& protocol, int statusCode, int size, const string& referer, 
			const string& userAgent)
		: resource(resource), infos(ip, userLogName, userName, dateTime, method, protocol, statusCode, size, referer, userAgent) {}

	~Request() {
		cerr << "Deleting request" << endl;
		delete infos.dateTime;
	}

	friend ostream& operator<<(ostream& os, const Request& abonne);
	friend istream& operator>>(istream& is, Request& abonne);

	friend class Graph;
	friend class Infos;

private:
	string resource;
	Infos infos;
};

#endif // REQUEST_H