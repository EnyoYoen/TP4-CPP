#include "Graph.h"

#include <iostream>
#include <sstream>

bool sortHits(const Hits& a, const Hits& b) {
    return a.second > b.second;
}


Graph::Graph(const string& start, int hour, bool exclude)
    : exclude(exclude), hour(hour), nextVertexId(0) {
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

    if (isExtensionExcluded(req.resource) || isTimeExcluded(*req.infos.dateTime) || isStatusCodeCorrect(req.infos.statusCode)) {
        return;
    }

    requests[req.resource] = req.infos;


    const string& source = getSourceFromReferer(req.infos.referer);
    const string& resource = trimOptions(req.resource);

    if (vertices.find(source) == vertices.end()) {
        reverseVertices[nextVertexId] = source;
        vertices[source] = nextVertexId++;
    }
    if (vertices.find(resource) == vertices.end()) {
        reverseVertices[nextVertexId] = resource;
        vertices[resource] = nextVertexId++;
    }

    int sourceId = vertices[source];
    int resourceId = vertices[resource];


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
    os << "layout = fdp;" << endl; // Le layout qui marche le mieux pour le rendering
    for (const auto& vertex : graph.vertices) {
        os << "node" << vertex.second << " [label=\"" << (vertex.first.empty() ? "-" : vertex.first) << "\"];" << endl;
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
    string source = referer.substr(last == string::npos ? 0 : last, referer.size() - 1);
    return trimOptions(source);
}

const string Graph::trimOptions(const string& address) const {
    size_t option = address.find_first_of('?');
    string trimmedAddress = address.substr(0, option == string::npos ? address.size() : option);
    size_t jsessionid = address.find(";jsessionid");
    return trimmedAddress.substr(0, (jsessionid == string::npos) != 0 ? trimmedAddress.size() : jsessionid);
    
}

bool Graph::isExtensionExcluded(const string& resource) const {
    bool result = false;

    if (exclude) {
        size_t last = resource.find_last_of('.');
        if (last != string::npos) {
            const string extension = resource.substr(resource.find_last_of('.'));
            if (extension == ".css" || extension == ".js" || extension == ".png" || extension == ".jpg" || extension == ".gif" || extension == ".ico") {
                return true;
            }
        }
    }

    return result;
}

bool Graph::isTimeExcluded(const DateTime& dt) const {
    bool result = false;

    if (start != nullptr) {
        ll diff = dt.secondsBetween(*start);
        if (diff < 0 || diff >= 3600) {
            return true;
        }
    }

    if (hour != -1 && dt.getHour() != hour) {
        return true;
    }

    return result;
}

bool Graph::isStatusCodeCorrect(const int code) const {
    return !(code >= 200 && code < 400);
}