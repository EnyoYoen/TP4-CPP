#include "Reader.h"

#include <fstream>

Reader::Reader(const string& filename, const string& out, const string& start, bool exclude)
    : graph(start, exclude), filename(filename), out(out) {}

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

void Reader::writeGraph() {
    list<Hits> hits = graph.getMostHitResources();

    int count = 0;
    for (const auto& hit : hits) {
        count++;
        cout << hit.first << " (" << hit.second << " hits)" << endl;

        if (count == 10) {
            break;
        }
    }

    if (!out.empty()) {
        writeGraphToFile();
    }
}

void Reader::writeGraphToFile() {
    ofstream file(out);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    file << graph;

    file.close();
}