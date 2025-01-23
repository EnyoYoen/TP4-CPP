#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

using namespace std;

struct Infos {
    Infos() {}
    Infos(const string& ip, const string& userLogName, const string& userName,
          const string& dateTime, const string& method, const string& protocol, 
          int statusCode, int size, const string& referer, const string& userAgent)
        : ip(ip), userLogName(userLogName), userName(userName), dateTime(dateTime), 
          method(method), protocol(protocol), statusCode(statusCode), 
          size(size), referer(referer), userAgent(userAgent) {}

    string ip;
    string userLogName;
    string userName;
    string dateTime; // TODO : data struct to store date and time
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

    friend ostream& operator<<(ostream& os, const Request& abonne);
    friend istream& operator>>(istream& is, Request& abonne);

    friend class Graph;
    friend class Infos;

private:
    string resource;
    Infos infos;
};

#endif // REQUEST_H