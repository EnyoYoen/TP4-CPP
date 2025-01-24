#ifndef READER_H
#define READER_H

#include <string>

#include "Graph.h"

using namespace std;

/*
Cette classe permet de gérer toutes les opérations de fichiers
et de générer le graphe associé.
*/

class Reader {
public:
    Reader(const string& filename, const string& start = string(), int hour = -1, bool exclude = false);

    void readRequests();

    void writeGraph(const string& out);

private:
    void writeGraphToFile(const string& out);

    Graph graph;
    string filename;
    string out;
};

#endif // READER_H