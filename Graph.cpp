#include "Graph.h"

#include <iostream>
#include <sstream>

bool sortHits(const Hits& a, const Hits& b) {
    return a.second > b.second;
}


Graph::Graph(const int start, bool exclude)
    : exclude(exclude), start(start), nextVertexId(0) {}
Graph::Graph(const string& start, bool exclude)
    : exclude(exclude), nextVertexId(0) {
        if (!start.empty()) {
            this->start = new DateTime(start);
        } else {
           this->start = nullptr;
        }
    }

void Graph::unmarshalRequest(const string& rawRequest) {
    Request req;
    istringstream iss(rawRequest);
    iss >> req;

    if (isExtensionExcluded(req.resource) || isTimeExcluded(*req.infos.dateTime)) {
        return;
    }

    requests[req.resource] = req.infos;


    const string& source = getSourceFromReferer(req.infos.referer);
    
    if (vertices.find(source) == vertices.end()) {
        reverseVertices[nextVertexId] = source;
        vertices[source] = nextVertexId++;
    }
    if (vertices.find(req.resource) == vertices.end()) {
        reverseVertices[nextVertexId] = req.resource;
        vertices[req.resource] = nextVertexId++;
    }

    int sourceId = vertices[source];
    int resourceId = vertices[req.resource];


    if (edges.find(resourceId) == edges.end()) {
        edges[resourceId] = unordered_map<int, int>();
    }
    unordered_map<int, int> resourceMap = edges[resourceId];
    
    if (resourceMap.find(sourceId) == resourceMap.end()) {
        resourceMap[sourceId] = 1;
    } else {
        resourceMap[sourceId] += 1;
    }

    edges[resourceId] = resourceMap;
}

list<Hits> Graph::getMostHitResources() const {
    unordered_map<string, int> hits;

    for (const auto& edge : edges) {
        for (const auto& edge2 : edge.second) {
            const string& hit = reverseVertices.at(edge.first);
            if (hits.find(hit) == hits.end()) {
                hits[hit] = edge2.second;
            } else {
                hits[hit] += edge2.second;
            }
        }
    }

    list<Hits> result;
    for (const auto& hit : hits) {
        result.push_back(Hits(hit.first, hit.second));
    }

    result.sort(sortHits);

    return result;
}

ostream& operator<<(ostream& os, const Graph& graph) {
    os << "digraph {" << endl;
    for (const auto& vertex : graph.vertices) {
        os << "node" << vertex.second << " [label=\"" << vertex.first << "\"];" << endl;
    }
    for (const auto& edge : graph.edges) {
        for (const auto& edge2 : edge.second) {
            os << "node" << edge.first << " -> node" << edge2.first << " [label=\"" << edge2.second << "\"];" << endl;
        }
    }
    os << "}" << endl;

    return os;
}


const string Graph::getSourceFromReferer(const string& referer) const {
    size_t last = referer.find_last_of('/');
    return referer.substr(last == string::npos ? 0 : last, referer.size() - 1);
}

bool Graph::isExtensionExcluded(const string& resource) const {
    bool result = false;

    if (exclude) {
        const string extension = resource.substr(resource.find_last_of('.'));
        if (extension == ".css" || extension == ".js" || extension == ".png" || extension == ".jpg" || extension == ".gif") {
            return true;
        }
    }

    return result;
}

bool Graph::isTimeExcluded(const DateTime& dt) const {
    bool result = false;

    if (start != nullptr) {
        ll diff = dt.secondsBetween(*start);
        if (diff < 0 || diff >= 3600) {
            cout << "Diff: " << diff << endl;
            return true;
        }
    }

    return result;
}