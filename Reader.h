//---------- Interface de la classe <Reader> (fichier Reader.h) ----------------

#ifndef READER_H
#define READER_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>

//------------------------------------------------------ Include personnel
#include "Graph.h"



//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Reader>
// Cette classe permet de gérer toutes les opérations de fichiers et de générer le graphe associé.
//------------------------------------------------------------------------

class Reader
{
//----------------------------------------------------------------- PUBLIC
public:

//----------------------------------------------------- Méthodes publiques
    void writeGraph(const string &out);

    void readRequests();

//-------------------------------------------- Constructeurs - destructeur
    Reader(const string &filename, const string &fromReferer, const string &toRessource, const string &start = string(), int hour = -1, bool exclude = false);

    virtual ~Reader();

    
//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Méthodes privée
    void writeGraphToFile(const string &out);

//----------------------------------------------------- Attributs privées
    Graph graph;
    string filename;
    string out;
};

//-------------------------------- Autres définitions dépendantes de <Reader>

#endif // READER_H