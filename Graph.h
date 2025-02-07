//---------- Interface de la classe <Graph> (fichier Graph.h) ----------------
#ifndef GRAPH_H
#define GRAPH_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <list>
#include <map>
#include <unordered_map>

//------------------------------------------------------ Include personnel
#include "Request.h"
#include "DateTime.h"

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef pair<const string, int> Hits;
typedef pair<const int, int> Edge;
typedef pair<const string, int> Vertex;
typedef pair<const int, unordered_map<int, int>> EdgeMap;

//------------------------------------------------------------------------
// Rôle de la classe <Graph>
// Cette classe permet de représenter un graphe orienté, et de l'exporter au format .dot.
//------------------------------------------------------------------------


class Graph
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
    Graph(const string &fromReferer = string(), const string &toRessource = string(), const string &start = string(), int hour = -1, bool exclude = false);
    // Mode d'emploi :
    // Constructeur qui initialise le graphe
    // Contrat :
    //

    virtual ~Graph();
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Autres méthodes publiques
    void unmarshalRequest(const string &rawRequest);
    // Mode d'emploi :
    // Cette méthode parse une requête brute, extrait les informations pertinentes, et les ajoute au graphe.
    // Elle ajoute des sommets (vertices) et des arcs (edges) représentant les sites et leur fréquence d'accès.
    // Contrat :
    //

    list<Hits> getMostHitResources() const;
    // Mode d'emploi :
    // Cette méthode retourne une liste des ressources les plus demandées, triées par fréquence (du plus demandé au moins demandé)
    // Contrat :
    //

//-------------------------------------------- Surcharge d'opérateurs
    friend ostream &operator<<(ostream &os, const Graph &graph);
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes privées
    const string trimOptions(const string &address) const;
    const string getSourceFromReferer(const string &referer) const;
    bool isExtensionExcluded(const string &resource) const;
    bool isTimeExcluded(const DateTime &dt) const;
    bool isStatusCodeCorrect(const int code) const;
    bool isRefererCorrect(const string &referer) const;
    bool isRessourceCorrect(const string &ressource) const;

//----------------------------------------------------- Attributs privés
    string fromReferer;
    string toRessource;
    bool startSet;
    bool exclude;
    int hour;
    DateTime start;

    size_t nextVertexId;
    unordered_map<string, int> vertices;
    unordered_map<int, string> reverseVertices;
    unordered_map<int, unordered_map<int, int>> edges;
};

//-------------------------------- Autres définitions dépendantes de <Graph>

#endif // GRAPH_H