#ifndef READER_H
#define READER_H

#include <string>

#include "Graph.h"

using namespace std;

class Reader {
public:
    Reader(const string& filename, const string& out = string(), const string& start = string(), bool exclude = false);

    void readRequests();

    void writeGraph();

private:
    void writeGraphToFile();

    Graph graph;
    string filename;
    string out;
};

#endif // READER_H