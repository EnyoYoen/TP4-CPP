#include "Request.h"

istream& operator>>(istream& is, Request& req) {
    getline(is, req.infos.ip, ' ');
    getline(is, req.infos.userLogName, ' ');
    getline(is, req.infos.userName, ' ');
    string dtStr;
    getline(is, dtStr, ']');
    req.infos.dateTime = new DateTime(dtStr);
    is.ignore(2); // Ignore the space and the opening quote
    getline(is, req.infos.method, ' ');
    getline(is, req.resource, ' ');
    getline(is, req.infos.protocol, '"');
    is.ignore(1); // Ignore the space
    is >> req.infos.statusCode;
    is >> req.infos.size;
    is.ignore(2); // Ignore the space and the opening quote
    getline(is, req.infos.referer, '"');
    is.ignore(2); // Ignore the space and the opening quote
    getline(is, req.infos.userAgent, '"');

    return is;
}

ostream& operator<<(ostream& os, const Request& req) {
    os << req.infos.ip << " " << req.infos.userLogName << " " << req.infos.userName << " " << *req.infos.dateTime << "] \"" << req.infos.method << " " << req.resource << " " << req.infos.protocol << "\" \"" << req.infos.userAgent << "\"";
    
    return os;
}