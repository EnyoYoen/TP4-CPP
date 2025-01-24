#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <map>
#include <unordered_map>

#include "Request.h"
#include "DateTime.h"

using namespace std;

/*
Cette classe permet de représenter un graphe orienté, et de l'exporter au format .dot.
*/

typedef pair<string, int> Hits;

class Graph {
public:
    Graph(const string& start = string(), int hour = -1, bool exclude = false);

    void unmarshalRequest(const string& rawRequest);

    list<Hits> getMostHitResources() const;

    friend ostream& operator<<(ostream& os, const Graph& graph);

private:
    const string trimOptions(const string& address) const;
    const string getSourceFromReferer(const string& referer) const;
    bool isExtensionExcluded(const string& resource) const;
    bool isTimeExcluded(const DateTime& dt) const;


    bool exclude;
    int hour;
    DateTime *start;

    size_t nextVertexId;
    unordered_map<string, int> vertices;
    unordered_map<int, string> reverseVertices;
    unordered_map<int, unordered_map<int, int>> edges;

    unordered_map<string, Infos> requests;
};

#endif // GRAPH_H