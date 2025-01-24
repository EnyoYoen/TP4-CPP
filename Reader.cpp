#include "Reader.h"

#include <fstream>

Reader::Reader(const string& filename, const int start, bool exclude)
    : graph(start, exclude), filename(filename) {}

void Reader::readRequests() {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    string line;
    while (getline(file, line)) {
        graph.unmarshalRequest(line);
    }

    file.close();
}

void Reader::writeGraph(const string& out) {
    list<Hits> hits = graph.getMostHitResources();
    for (const auto& hit : hits) {
        cout << hit.first << " (" << hit.second << " hits)" << endl;
    }

    if (!out.empty()) {
        writeGraphToFile(out);
    }
}

void Reader::writeGraphToFile(const string& out) {
    ofstream file(out);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    file << graph;

    file.close();
}